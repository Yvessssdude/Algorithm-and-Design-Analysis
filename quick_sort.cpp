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

//swap function (exchanging 2 data)
void swap(Data &a, Data &b) {
    Data temp = a;
    a = b;
    b = temp;
}

//place pivot element in the correct position and put smaller elements on the left while the larger on the right
int partition(vector<Data> &arr, int start, int end) {
    int pivot = arr[end].number; //last element as pivot
    int i = start - 1;

    for (int j = start; j < end; j++) {
        if (arr[j].number <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[end]); //move pivot to the correct position
    return i + 1;
}

void quickSort(vector<Data> &arr, int start, int end) {
    if (start < end) {
        int pi = partition(arr, start, end); //get pivot index
        quickSort(arr, start, pi - 1); //sort left side
        quickSort(arr, pi + 1, end); //sort right side
    }
}

int main() {
    ifstream file("dataset_27000000.csv"); //open file and read
    vector<Data> arr;
    string line;

    while (getline(file, line)) {
        size_t commaPos = line.find(',');
        string numPart = line.substr(0, commaPos); //get the number
        string wordPart = line.substr(commaPos + 1); //get the string
        int num = stoi(numPart); //conversion from str to int

        Data data;
        data.number = num;
        data.word = wordPart;
        arr.push_back(data); //add to the vector
    }
    file.close();

    clock_t start = clock(); //start time
    quickSort(arr, 0, arr.size() - 1); //perform sorting
    clock_t end = clock(); //stop time

    //open the output file and save the sorted data
    ofstream output("quick_sort_" + to_string(arr.size()) + ".csv");
    for (int i = 0; i < arr.size(); i++) {
        output << arr[i].number << "," << arr[i].word << endl;
    }
    output.close();

    //calculate running time
    double duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Running time: " << duration << " seconds" << endl;

    return 0;
}
