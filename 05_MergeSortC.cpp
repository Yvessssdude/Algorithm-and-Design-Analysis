#include <iostream> //05_MergeSortC.cpp
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

// Data structure to hold ID and name pairs
struct Record {
    long long id;
    string name;
    
    Record(long long i = 0, string n = "") : id(i), name(n) {}
};

class MergeSort {
private:
    vector<Record> records;  // Store all data from CSV
    
    // Merge two sorted halves into one sorted array
    void merge(vector<Record>& arr, int left, int mid, int right) {
        vector<Record> leftArr, rightArr;
        
        // Copy left half
        for (int i = left; i <= mid; i++) {
            leftArr.push_back(arr[i]);
        }
        
        // Copy right half
        for (int i = mid + 1; i <= right; i++) {
            rightArr.push_back(arr[i]);
        }
        
        // Merge back into original array
        int i = 0, j = 0, k = left;
        while (i < leftArr.size() && j < rightArr.size()) {
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
        while (i < leftArr.size()) {
            arr[k] = leftArr[i];
            i++;
            k++;
        }
        while (j < rightArr.size()) {
            arr[k] = rightArr[j];
            j++;
            k++;
        }
    }
    
    // Recursive merge sort
    void mergeSort(vector<Record>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }
    
public:
    // Load data from CSV file
    bool loadFile(string filename) {
        ifstream file(filename);
        if (!file.is_open()) return false;
        
        string line;
        while (getline(file, line)) {
            int pos = line.find(',');
            if (pos != string::npos) {
                try {
                    long long id = stoll(line.substr(0, pos));
                    string name = line.substr(pos + 1);
                    records.push_back(Record(id, name));
                } catch (...) {
                    // Skip invalid lines
                }
            }
        }
        file.close();
        return !records.empty();
    }
    
    // Perform merge sort and save to CSV
    void sortAndSave() {
        // Start timing
        auto startTime = chrono::high_resolution_clock::now();
        
        // Perform merge sort
        mergeSort(records, 0, records.size() - 1);
        
        // Save sorted data to CSV
        ofstream outFile("merge_sort_1000000.csv");
        for (const auto& record : records) {
            outFile << record.id << "," << record.name << endl;
        }
        outFile.close();
        
        // Calculate and print execution time
        auto endTime = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
        cout <<  "Running time: " << duration.count() / 1000000.0 << " seconds" << endl;
    }
};

int main() {
    MergeSort sorter;
    
    // Load dataset from CSV file
    if (!sorter.loadFile("dataset_1000000.csv")) {
        return 1;
    }
    
    // Sort and save to output CSV
    sorter.sortAndSave();
    
    return 0;
}