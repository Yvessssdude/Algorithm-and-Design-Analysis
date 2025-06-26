#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>

struct DataRecord {
    long long id;
    std::string name;
    
    DataRecord(long long id = 0, const std::string& name = "") : id(id), name(name) {}
};

class BinarySearchStep {
private:
    std::vector<DataRecord> data;
    
public:
    bool loadDataset(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Error: Could not open file " << filename << std::endl;
            return false;
        }
        
        std::string line;
        
        // Read first line and check if it's a header or data
        if (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string firstPart, secondPart;
            
            if (std::getline(ss, firstPart, ',') && std::getline(ss, secondPart)) {
                try {
                    long long id = std::stoll(firstPart);
                    // If successful, this is data, not a header
                    data.emplace_back(id, secondPart);
                } catch (const std::exception& e) {
                    // If parsing fails, this is likely a header - skip it
                }
            }
        }
        
        // Continue reading the rest of the file
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string idStr, name;
            
            if (std::getline(ss, idStr, ',') && std::getline(ss, name)) {
                try {
                    long long id = std::stoll(idStr);
                    data.emplace_back(id, name);
                } catch (const std::exception& e) {
                    std::cout << "Error parsing line: " << line << std::endl;
                }
            }
        }
        
        file.close();
        std::cout << "Loaded " << data.size() << " records from " << filename << std::endl;
        return !data.empty();
    }
    
    void binarySearchWithSteps(long long target) {
        auto totalStart = std::chrono::high_resolution_clock::now();
        
        // Create output filename: binary_search_step_target.txt
        std::string filename = "binary_search_step_" + std::to_string(target) + ".txt";
        std::ofstream outFile(filename);
        
        if (!outFile.is_open()) {
            std::cout << "Error creating output file!" << std::endl;
            return;
        }
        
        std::cout << "Starting binary search for target: " << target << std::endl;
        auto searchStart = std::chrono::high_resolution_clock::now();
        
        int left = 0;
        int right = data.size() - 1;
        bool found = false;
        int comparisons = 0;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            comparisons++;
            
            // Write search step to file (row number is 1-based)
            outFile << (mid + 1) << ": " << data[mid].id << "/" << data[mid].name << std::endl;
            
            if (data[mid].id == target) {
                found = true;
                break;
            } else if (data[mid].id < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        auto searchEnd = std::chrono::high_resolution_clock::now();
        auto searchDuration = std::chrono::duration_cast<std::chrono::microseconds>(searchEnd - searchStart);
        
        // If target not found, add -1 at the end
        if (!found) {
            outFile << "-1" << std::endl;
        }
        
        outFile.close();
        
        auto totalEnd = std::chrono::high_resolution_clock::now();
        auto totalDuration = std::chrono::duration_cast<std::chrono::milliseconds>(totalEnd - totalStart);
        
        std::cout << "\n=== BINARY SEARCH COMPLETED ===" << std::endl;
        if (found) {
            std::cout << "Target " << target << " FOUND!" << std::endl;
        } else {
            std::cout << "Target " << target << " NOT FOUND!" << std::endl;
        }
        std::cout << "Search time: " << searchDuration.count() / 1000.0 << " ms" << std::endl;
        std::cout << "Total process time: " << totalDuration.count() << " ms" << std::endl;
        std::cout << "Comparisons made: " << comparisons << std::endl;
        std::cout << "Search path saved to: " << filename << std::endl;
    }
    
    int getDataSize() const {
        return data.size();
    }
    
    // Helper function to display some data for testing
    void displaySampleData() {
        std::cout << "\n=== SAMPLE DATA FROM DATASET ===" << std::endl;
        std::cout << "First 5 records:" << std::endl;
        for (size_t i = 0; i < std::min((size_t)5, data.size()); i++) {
            std::cout << "Row " << (i + 1) << ": " << data[i].id << "/" << data[i].name << std::endl;
        }
        
        std::cout << "\nMiddle 3 records:" << std::endl;
        size_t mid = data.size() / 2;
        for (size_t i = mid - 1; i <= mid + 1 && i < data.size(); i++) {
            std::cout << "Row " << (i + 1) << ": " << data[i].id << "/" << data[i].name << std::endl;
        }
        
        std::cout << "\nLast 5 records:" << std::endl;
        size_t start = data.size() >= 5 ? data.size() - 5 : 0;
        for (size_t i = start; i < data.size(); i++) {
            std::cout << "Row " << (i + 1) << ": " << data[i].id << "/" << data[i].name << std::endl;
        }
        std::cout << "=================================" << std::endl;
    }
};

int main() {
    BinarySearchStep searcher;
    
    // Load the quick_sort_1000.csv dataset
    std::string filename = "quick_sort_1000.csv";
    
    std::cout << "=== BINARY SEARCH STEP PROGRAM ===" << std::endl;
    std::cout << "Loading dataset: " << filename << std::endl;
    
    if (!searcher.loadDataset(filename)) {
        std::cout << "Failed to load dataset!" << std::endl;
        return 1;
    }
    
    // Display sample data to help choose targets
    searcher.displaySampleData();
    
    // Get target from user
    long long target;
    std::cout << "\n=== TARGET INPUT ===" << std::endl;
    std::cout << "Enter the target ID to search for: ";
    std::cin >> target;
    
    std::cout << "\nSearching for target: " << target << std::endl;
    std::cout << "Output will be saved to: binary_search_step_" << target << ".txt" << std::endl;
    
    // Perform binary search with step tracking
    searcher.binarySearchWithSteps(target);
    
    return 0;
}
