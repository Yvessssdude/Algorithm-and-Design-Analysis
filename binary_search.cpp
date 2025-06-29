#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

struct Data {
    int key; //(for number)
    string value; //(for alphabet)
};

// Load dataset from file
vector<Data> loadDataset(const string& filename) {
    vector<Data> data;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        size_t comma = line.find(','); 
        if (comma != string::npos) {
            try {
                int key = stoi(line.substr(0, comma));
                string value = line.substr(comma + 1);
                data.push_back({key, value});
            } catch (...) {
                continue;
            }
        }
    }

    return data;
}

// function for binary search
int binarySearch(const vector<Data>& data, int target) {
    int left = 0;
    int right = data.size() - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (data[mid].key == target) return mid;
        else if (data[mid].key < target) left = mid + 1;
        else right = mid - 1;
    }

    return -1;
}

// measure search times for each data
vector<double> measureSearchTimes(const vector<Data>& data) {
    vector<double> times;
    // Loops through every key(number) in the dataset
    for (const auto& item : data) {
        int target = item.key;
        auto start = high_resolution_clock::now();
        binarySearch(data, target);
        auto end = high_resolution_clock::now();
        //convert microseconds into milliseconds
        double duration = duration_cast<microseconds>(end - start).count() / 1000.0;
        times.push_back(duration);
    }

    return times;
}

// Save best, average and worst case into file
void saveResults(const string& filename, const vector<double>& times) {
    double best = times[0], worst = times[0], sum = 0;

    for (double t : times) {
        if (t < best) best = t;
        if (t > worst) worst = t;
        sum += t;
    }

    double average = sum / times.size();

    ofstream out(filename);
    out << "Best case time   : " << best << " ms\n";
    out << "Average case time: " << average << " ms\n";
    out << "Worst case time  : " << worst << " ms\n";
    out.close();

    cout << "Results saved to: " << filename << endl;
}

// Main
int main() {
    int data_size;
    cout << "Enter dataset size : ";
    cin >> data_size;

    string inputFile = "merge_sort_" + to_string(data_size) + ".csv";
    string outputFile = "binary_search_" + to_string(data_size) + ".txt";

    vector<Data> data = loadDataset(inputFile);

    if (data.empty()) {
        cout << "Failed to load data from file: " << inputFile << endl;
        return 1;
    }

    vector<double> times = measureSearchTimes(data);
    saveResults(outputFile, times);

    return 0;
}
