#include <iostream> //07_BinarySearchCStep.cpp
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

class BinarySearchStep {
private:
    vector<Record> data;    // All records from CSV
    
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
    
    // Perform binary search with step recording
    void searchWithSteps(long long target) {
        // Start timing
        auto startTime = chrono::high_resolution_clock::now();
        
        // Create output file
        string filename = "binary_search_step_" + to_string(target) + ".txt";
        ofstream outFile(filename);
        
        // Binary search variables
        int left = 0;
        int right = data.size() - 1;
        bool found = false;
        
        // Perform binary search
        while (left <= right) {
            // Find middle position
            int mid = left + (right - left) / 2;
            
            // Write current step to file (1-based position)
            outFile << (mid + 1) << ": " << data[mid].id << "/" << data[mid].name << endl;
            
            // Check if target found
            if (data[mid].id == target) {
                found = true;
                break;
            }
            // Target is in right half
            else if (data[mid].id < target) {
                left = mid + 1;
            }
            // Target is in left half
            else {
                right = mid - 1;
            }
        }
        
        // If target not found, write -1
        if (!found) {
            outFile << "-1" << endl;
        }
        
        // Close file
        outFile.close();
        
        // Calculate and print running time
        auto endTime = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
        cout << "Running time: " << duration.count() / 1000000.0 << " seconds" << endl;
    }
    
    // Get data size
    int getSize() {
        return data.size();
    }
};

int main() {
    BinarySearchStep searcher;
    
    // Load the dataset (need to keep changing the number before run new datasets)
    if (!searcher.loadData("quick_sort_1000000.csv")) {
        return 1;
    }
    
    // Get target from user
    long long target;
    cout << "Enter target to search: ";
    cin >> target;
    
    // Perform binary search and show running time
    searcher.searchWithSteps(target);
    
    return 0;
}