#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <algorithm>

struct DataRecord {
    long long id;
    std::string name;
    
    DataRecord(long long id = 0, const std::string& name = "") : id(id), name(name) {}
    
    // For sorting by ID
    bool operator<(const DataRecord& other) const {
        return id < other.id;
    }
};

class MergeSort {
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
        std::cout << "Loaded " << data.size() << " records" << std::endl;
        return !data.empty();
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
    
    void mergeSort(std::vector<DataRecord>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }
    
    void performMergeSort() {
        if (data.empty()) {
            std::cout << "No data to sort!" << std::endl;
            return;
        }
        
        // Record start time
        auto start = std::chrono::high_resolution_clock::now();
        
        // Perform merge sort
        mergeSort(data, 0, data.size() - 1);
        
        // Record end time
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        // Print running time
        std::cout << "Merge sort completed in " << duration.count() << " ms" << std::endl;
        
        // Save sorted data to CSV
        saveSortedData();
    }
    
    void saveSortedData() {
        std::string outputFilename = "merge_sort_" + std::to_string(data.size()) + ".csv";
        std::ofstream outFile(outputFilename);
        
        if (!outFile.is_open()) {
            std::cout << "Error creating output file!" << std::endl;
            return;
        }
        
        // Write sorted data to CSV (no header)
        for (const auto& record : data) {
            outFile << record.id << "," << record.name << std::endl;
        }
        
        outFile.close();
        std::cout << "Sorted data saved to " << outputFilename << std::endl;
        
        // Display first 5 rows
        std::cout << "\nFirst 5 rows of sorted data:" << std::endl;
        for (size_t i = 0; i < std::min((size_t)5, data.size()); i++) {
            std::cout << data[i].id << "," << data[i].name << std::endl;
        }
    }
    
    int getDataSize() const {
        return data.size();
    }
};

int main() {
    MergeSort sorter;
    
    // Load dataset - you can change this filename as needed
    std::string filename = "dataset_sample_1000.csv";
    
    if (!sorter.loadDataset(filename)) {
        std::cout << "Failed to load dataset!" << std::endl;
        return 1;
    }
    
    // Perform merge sort and save results
    sorter.performMergeSort();
    
    return 0;
}
