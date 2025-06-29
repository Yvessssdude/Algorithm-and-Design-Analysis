#include <iostream> 
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

// Simple structure to hold record data
struct Record {
    long long id;
    string name;
    
    Record(long long i = 0, string n = "") : id(i), name(n) {}
};

class MergeSortStep {
private:
    vector<Record> data;    // All records from CSV
    ofstream outFile;       // Output file for steps
    
    // Write array state to file
    void writeArray(vector<Record>& arr) {
        outFile << "[";
        for (int i = 0; i < arr.size(); i++) {
            outFile << arr[i].id << "/" << arr[i].name;
            if (i < arr.size() - 1) {
                outFile << ", ";
            }
        }
        outFile << "]" << endl;
    }
    
    // Merge two sorted parts
    void merge(vector<Record>& arr, int left, int mid, int right) {
        // Create temporary arrays for left and right parts
        vector<Record> leftPart, rightPart;
        
        // Copy left half
        for (int i = left; i <= mid; i++) {
            leftPart.push_back(arr[i]);
        }
        
        // Copy right half
        for (int i = mid + 1; i <= right; i++) {
            rightPart.push_back(arr[i]);
        }
        
        // Merge the two parts back
        int i = 0, j = 0, k = left;
        
        // Compare and merge
        while (i < leftPart.size() && j < rightPart.size()) {
            if (leftPart[i].id <= rightPart[j].id) {
                arr[k] = leftPart[i];
                i++;
            } else {
                arr[k] = rightPart[j];
                j++;
            }
            k++;
        }
        
        // Copy remaining elements from left
        while (i < leftPart.size()) {
            arr[k] = leftPart[i];
            i++;
            k++;
        }
        
        // Copy remaining elements from right
        while (j < rightPart.size()) {
            arr[k] = rightPart[j];
            j++;
            k++;
        }
    }
    
    // Recursive merge sort with step recording
    void mergeSortSteps(vector<Record>& arr, int left, int right) {
        if (left < right) {
            // Find middle point
            int mid = left + (right - left) / 2;
            
            // Sort left half
            mergeSortSteps(arr, left, mid);
            
            // Sort right half
            mergeSortSteps(arr, mid + 1, right);
            
            // Merge the sorted halves
            merge(arr, left, mid, right);
            
            // Record this step in output file
            writeArray(arr);
        }
    }
    
public:
    // Load data from CSV file
    bool loadData(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        
        string line;
        // Read each line
        while (getline(file, line)) {
            int commaPos = line.find(',');
            if (commaPos != string::npos) {
                try {
                    // Extract ID and name
                    long long id = stoll(line.substr(0, commaPos));
                    string name = line.substr(commaPos + 1);
                    data.push_back(Record(id, name));
                } catch (...) {
                    // Skip bad lines
                }
            }
        }
        file.close();
        return !data.empty();
    }
    
    // Main sorting function
    void performSort(int startRow, int endRow) {
        // Check if range is valid
        if (startRow < 1 || endRow > data.size() || startRow > endRow) {
            return;
        }
        
        // Start timing
        auto startTime = chrono::high_resolution_clock::now();
        
        // Get subset of data to sort
        vector<Record> subset;
        for (int i = startRow - 1; i < endRow; i++) {
            subset.push_back(data[i]);
        }
        
        // Create output file
        string filename = "merge_sort_step_" + to_string(startRow) + "_" + to_string(endRow) + ".txt";
        outFile.open(filename);
        
        // Write initial state
        writeArray(subset);
        
        // Perform merge sort with step recording
        mergeSortSteps(subset, 0, subset.size() - 1);
        
        // Close file
        outFile.close();
        
        // Calculate and print time
        auto endTime = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
        cout <<  "Running time: " << duration.count() / 1000000.0 << " seconds"  << endl;
    }
    
    // Get data size
    int getSize() {
        return data.size();
    }
};

int main() {
    MergeSortStep sorter;
    
    // Load the dataset
    if (!sorter.loadData("dataset_sample_1000000.csv")) {
        return 1;
    }
    
    // Get input from user with clear prompts
    int start, end;
    cout << "Enter start row: ";
    cin >> start;
    cout << "Enter end row: ";
    cin >> end;
    
    // Perform sorting and show running time
    sorter.performSort(start, end);
    
    return 0;
}