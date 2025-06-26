#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <random>

struct DataRecord {
    long long id;
    std::string name;
    
    DataRecord(long long id = 0, const std::string& name = "") : id(id), name(name) {}
};

class BinarySearchAnalysis {
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
    
    bool binarySearch(long long target) {
        int left = 0;
        int right = data.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (data[mid].id == target) {
                return true;
            } else if (data[mid].id < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return false;
    }
    
    double measureSearchTime(const std::vector<long long>& targets) {
        auto start = std::chrono::high_resolution_clock::now();
        
        for (long long target : targets) {
            binarySearch(target);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        return duration.count() / 1000.0; // Convert to milliseconds
    }
    
    void performAnalysis() {
        if (data.empty()) {
            std::cout << "No data to analyze!" << std::endl;
            return;
        }
        
        size_t n = data.size();
        
        // Best case: Search for middle element n times (found in first comparison)
        std::vector<long long> bestCaseTargets(n, data[n / 2].id);
        double bestTime = measureSearchTime(bestCaseTargets);
        
        // Average case: Search for random existing elements n times
        std::vector<long long> avgCaseTargets;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, data.size() - 1);
        
        for (size_t i = 0; i < n; i++) {
            avgCaseTargets.push_back(data[dis(gen)].id);
        }
        double avgTime = measureSearchTime(avgCaseTargets);
        
        // Worst case: Search for non-existent element n times (searches entire tree)
        long long maxId = std::max_element(data.begin(), data.end(), 
            [](const DataRecord& a, const DataRecord& b) { return a.id < b.id; })->id;
        std::vector<long long> worstCaseTargets(n, maxId + 1);
        double worstTime = measureSearchTime(worstCaseTargets);
        
        // Create output filename
        std::string outputFilename = "binary_search_" + std::to_string(n) + ".txt";
        std::ofstream outFile(outputFilename);
        
        if (!outFile.is_open()) {
            std::cout << "Error creating output file!" << std::endl;
            return;
        }
        
        // Write ONLY the three required lines to file
        outFile << "Best case time   : " << bestTime << " ms" << std::endl;
        outFile << "Average case time: " << avgTime << " ms" << std::endl;
        outFile << "Worst case time  : " << worstTime << " ms" << std::endl;
        
        outFile.close();
        
        // Display results on console
        std::cout << "\nBinary Search Analysis Completed!" << std::endl;
        std::cout << "Dataset size: " << n << std::endl;
        std::cout << "Searches performed per case: " << n << std::endl;
        std::cout << "Results saved to: " << outputFilename << std::endl;
        std::cout << "\nTiming Results:" << std::endl;
        std::cout << "Best case time   : " << bestTime << " ms" << std::endl;
        std::cout << "Average case time: " << avgTime << " ms" << std::endl;
        std::cout << "Worst case time  : " << worstTime << " ms" << std::endl;
    }
    
    int getDataSize() const {
        return data.size();
    }
};

int main() {
    BinarySearchAnalysis analyzer;
    
    // Load the merge_sort_1000000.csv dataset
    std::string filename = "merge_sort_1000000.csv";
    
    std::cout << "=== BINARY SEARCH PERFORMANCE ANALYSIS ===" << std::endl;
    std::cout << "Loading dataset: " << filename << std::endl;
    
    if (!analyzer.loadDataset(filename)) {
        std::cout << "Failed to load dataset!" << std::endl;
        return 1;
    }
    
    std::cout << "Starting binary search analysis..." << std::endl;
    std::cout << "This may take a moment for large datasets..." << std::endl;
    
    // Perform the analysis
    analyzer.performAnalysis();
    
    return 0;
}
