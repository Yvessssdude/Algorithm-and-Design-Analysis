#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

struct Data {
    int number;
    string word;
};

vector<Data> arr;
int startRow, endRow;

void swap(Data &a, Data &b) {
    Data temp = a;
    a = b;
    b = temp;
}

void printArrayToFile(string filename, int pi) {
    ofstream file(filename, ios::app);
    if (pi != -1) {
        file << "pi=" << pi << " ";
    }
    file << "[";
    for (int i = 0; i < arr.size(); i++) {
        file << arr[i].number << "/" << arr[i].word;
        if (i < arr.size() - 1) file << ", ";
    }
    file << "]" << endl;
    file.close();
}

int partition(int start, int end) {
    int pivot = arr[end].number;
    int i = start - 1;

    for (int j = start; j < end; j++) {
        if (arr[j].number <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[end]);
    return i + 1;
}

void quickSort(int start, int end, string filename) {
    if (start < end) {
        int pi = partition(start, end);
        printArrayToFile(filename, pi);
        quickSort(start, pi - 1, filename);
        quickSort(pi + 1, end, filename);
    }
}

int main() {
    cout << "Enter starting row: ";
    cin >> startRow;
    cout << "Enter ending row: ";
    cin >> endRow;

    ifstream file("dataset_sample_1000(1).csv");
    string line;
    int currentLine = 1;

    while (getline(file, line)) {
        if (currentLine >= startRow && currentLine <= endRow) {
            size_t commaPos = line.find(',');
            string numPart = line.substr(0, commaPos);
            string wordPart = line.substr(commaPos + 1);
            int num = stoi(numPart);

            Data data;
            data.number = num;
            data.word = wordPart;
            arr.push_back(data);
        }
        currentLine++;
        if (currentLine > endRow) break;
    }
    file.close();

    string filename = "quick_sort_step_" + to_string(startRow) + "_" + to_string(endRow) + ".txt";

    // print original array before sorting
    printArrayToFile(filename, -1);

    clock_t start = clock();
    quickSort(0, arr.size() - 1, filename);
    clock_t end = clock();

    double duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Running time: " << duration << " seconds" << endl;

    return 0;
}
