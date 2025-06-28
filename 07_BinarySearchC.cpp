#include <iostream> //07_BinarySearchC.cpp
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;

// Simple structure to hold record data
struct Record {
    long long id;
    string name;
    
    Record(long long i = 0, string n = "") : id(i), name(n) {}
};

class BinarySearchAnalysis {
private:
    vector<Record> data;    // All records from CSV
    int datasetSize;        // Actual number of records loaded
    
    // Perform single binary search
    bool binarySearch(long long target) {
        int left = 0;
        int right = data.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (data[mid].id == target) {
                return true;
            }
            else if (data[mid].id < target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return false;
    }
    
    // Measure search time for multiple targets
    double measureSearchTime(vector<long long>& targets) {
        auto startTime = chrono::high_resolution_clock::now();
        
        // Perform searches
        for (long long target : targets) {
            binarySearch(target);
        }
        
        auto endTime = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
        return duration.count() / 1000.0; // Convert to milliseconds
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
        
        // Store the actual number of records loaded
        datasetSize = data.size();
        
        return !data.empty();
    }
    
    // Perform analysis for all three cases
    void performAnalysis() {
        int n = data.size();
        
        // Prepare targets for each case
        vector<long long> bestCaseTargets;
        vector<long long> avgCaseTargets;
        vector<long long> worstCaseTargets;
        
        // Best case: middle element (found in first comparison)
        long long middleId = data[n / 2].id;
        for (int i = 0; i < n; i++) {
            bestCaseTargets.push_back(middleId);
        }
        
        // Average case: random existing elements
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, data.size() - 1);
        for (int i = 0; i < n; i++) {
            avgCaseTargets.push_back(data[dis(gen)].id);
        }
        
        // Worst case: non-existent element (searches entire tree)
        long long maxId = data[data.size() - 1].id; // Last element (highest ID)
        for (int i = 0; i < n; i++) {
            worstCaseTargets.push_back(maxId + 1);
        }
        
        // Measure times for each case
        double bestTime = measureSearchTime(bestCaseTargets);
        double avgTime = measureSearchTime(avgCaseTargets);
        double worstTime = measureSearchTime(worstCaseTargets);
        
        // Create output filename using actual dataset size
        string outputFilename = "binary_search_" + to_string(datasetSize) + ".txt";
        ofstream outFile(outputFilename);
        
        // Write results to file
        outFile << "Best case time   : " << bestTime << " ms" << endl;
        outFile << "Average case time: " << avgTime << " ms" << endl;
        outFile << "Worst case time  : " << worstTime << " ms" << endl;
        
        outFile.close();
        
        // Print confirmation to terminal
        cout << "Output has been saved to " << outputFilename << endl;
    }
    
    // Get data size
    int getSize() {
        return data.size();
    }
};

int main() {
    BinarySearchAnalysis analyzer;
    
    // Load the dataset
    if (!analyzer.loadData("merge_sort_1000000.csv")) {
        return 1;
    }
    
    // Perform binary search analysis
    analyzer.performAnalysis();
    
    return 0;
}