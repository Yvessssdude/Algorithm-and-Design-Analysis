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

class MergeSortStep {
private:
    std::vector<DataRecord> data;
    std::ofstream* outputFile;
    
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
                // Try to parse the first part as a number
                try {
                    long long id = std::stoll(firstPart);
                    // If successful, this is data, not a header
                    data.emplace_back(id, secondPart);
                    std::cout << "First line is data: " << id << "/" << secondPart << std::endl;
                } catch (const std::exception& e) {
                    // If parsing fails, this is likely a header
                    std::cout << "First line is header: " << line << std::endl;
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
        
        // Debug: Print first few records
        std::cout << "First 5 records loaded:" << std::endl;
        for (size_t i = 0; i < std::min((size_t)5, data.size()); i++) {
            std::cout << "Row " << (i + 1) << ": " << data[i].id << "/" << data[i].name << std::endl;
        }
        
        return !data.empty();
    }
    
    void printArray(const std::vector<DataRecord>& arr) {
        *outputFile << "[";
        for (size_t i = 0; i < arr.size(); i++) {
            *outputFile << arr[i].id << "/" << arr[i].name;
            if (i < arr.size() - 1) {
                *outputFile << ", ";
            }
        }
        *outputFile << "]" << std::endl;
    }
    
    void merge(std::vector<DataRecord>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        
        std::vector<DataRecord> leftArr(n1);
        std::vector<DataRecord> rightArr(n2);
        
        // Copy data to temp arrays
        for (int i = 0; i < n1; i++)
            leftArr[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            rightArr[j] = arr[mid + 1 + j];
        
        // Merge the temp arrays back
        int i = 0, j = 0, k = left;
        
        while (i < n1 && j < n2) {
            if (leftArr[i].id <= rightArr[j].id) {
                arr[k] = leftArr[i];
                i++;
            } else {
                arr[k] = rightArr[j];
                j++;
            }
            k++;
        }
        
        // Copy remaining elements
        while (i < n1) {
            arr[k] = leftArr[i];
            i++;
            k++;
        }
        
        while (j < n2) {
            arr[k] = rightArr[j];
            j++;
            k++;
        }
    }

    void mergeSortWithSteps(std::vector<DataRecord>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
        
            mergeSortWithSteps(arr, left, mid);
            mergeSortWithSteps(arr, mid + 1, right);
            merge(arr, left, mid, right);
            
            // Print array state after each merge
            printArray(arr);
        }
    }

    void performMergeSort(int startRow, int endRow) {
        if (startRow < 1 || endRow > data.size() || startRow > endRow) {
            std::cout << "Invalid row range!" << std::endl;
            return;
        }

        auto totalStart = std::chrono::high_resolution_clock::now();

        // Convert to 0-based indexing
        int start = startRow - 1;
        int end = endRow - 1;

        // Extract subset
        std::vector<DataRecord> subset(data.begin() + start, data.begin() + end + 1);

        // Debug: Show the subset we're sorting
        std::cout << "Sorting subset from row " << startRow << " to " << endRow << ":" << std::endl;
        for (size_t i = 0; i < subset.size(); i++) {
            std::cout << "Position " << i << ": " << subset[i].id << "/" << subset[i].name << std::endl;
        }

        // Create output filename
        std::string filename = "merge_sort_step_" + std::to_string(startRow) + "_" + std::to_string(endRow) + ".txt";
        std::ofstream outFile(filename);

        if (!outFile.is_open()) {
            std::cout << "Error creating output file!" << std::endl;
            return;
        }

        outputFile = &outFile;

        // Print initial array
        printArray(subset);

        std::cout << "Starting merge sort process..." << std::endl;
        auto sortStart = std::chrono::high_resolution_clock::now();
        
        // Perform merge sort with step tracking
        mergeSortWithSteps(subset, 0, subset.size() - 1);
        
        auto sortEnd = std::chrono::high_resolution_clock::now();
        auto sortDuration = std::chrono::duration_cast<std::chrono::microseconds>(sortEnd - sortStart);

        outFile.close();
        
        auto totalEnd = std::chrono::high_resolution_clock::now();
        auto totalDuration = std::chrono::duration_cast<std::chrono::milliseconds>(totalEnd - totalStart);
        
        std::cout << "\n=== MERGE SORT COMPLETED ===" << std::endl;
        std::cout << "Sorting time: " << sortDuration.count() / 1000.0 << " ms" << std::endl;
        std::cout << "Total process time: " << totalDuration.count() << " ms" << std::endl;
        std::cout << "Elements sorted: " << subset.size() << std::endl;
        std::cout << "Output saved to: " << filename << std::endl;
    }
    
    int getDataSize() const {
        return data.size();
    }
};

int main() {
    MergeSortStep sorter;
    
    // Load dataset
    if (!sorter.loadDataset("dataset_sample_1000.csv")) {
        std::cout << "Failed to load dataset!" << std::endl;
        return 1;
    }
    
    std::cout << "Dataset loaded successfully! Total rows: " << sorter.getDataSize() << std::endl;
    
    // Get user input
    int startRow, endRow;
    std::cout << "Enter start row (1 to " << sorter.getDataSize() << "): ";
    std::cin >> startRow;
    
    std::cout << "Enter end row (1 to " << sorter.getDataSize() << "): ";
    std::cin >> endRow;
    
    // Perform merge sort
    sorter.performMergeSort(startRow, endRow);
    
    return 0;
}
