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

void swap(Data &a, Data &b) {
    Data temp = a;
    a = b;
    b = temp;
}

int partition(vector<Data> &arr, int start, int end) {
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

void quickSort(vector<Data> &arr, int start, int end) {
    if (start < end) {
        int pi = partition(arr, start, end);
        quickSort(arr, start, pi - 1);
        quickSort(arr, pi + 1, end);
    }
}

int main() {
    ifstream file("dataset_1000000.csv");
    vector<Data> arr;
    string line;

    while (getline(file, line)) {
        size_t commaPos = line.find(',');
        string numPart = line.substr(0, commaPos);
        string wordPart = line.substr(commaPos + 1);
        int num = stoi(numPart);

        Data data;
        data.number = num;
        data.word = wordPart;
        arr.push_back(data);
    }
    file.close();

    clock_t start = clock();
    quickSort(arr, 0, arr.size() - 1);
    clock_t end = clock();

    ofstream output("quick_sort_" + to_string(arr.size()) + ".csv");
    for (int i = 0; i < arr.size(); i++) {
        output << arr[i].number << "," << arr[i].word << endl;
    }
    output.close();

    double duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Running time: " << duration << " seconds" << endl;

    return 0;
}
