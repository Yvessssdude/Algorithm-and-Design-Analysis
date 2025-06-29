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

//global vector (storing data record)
vector<Data> arr;
int startRow, endRow;

//swap function (exchanging 2 data)
void swap(Data &a, Data &b) {
    Data temp = a;
    a = b;
    b = temp;
}

void printArrayToFile(string filename, int pi) {
    ofstream file(filename, ios::app); 

    //print pivot index if available
    if (pi != -1) {
        file << "pi=" << pi << " ";
    }

    //print all elements in the array
    file << "[";
    for (int i = 0; i < arr.size(); i++) {
        file << arr[i].number << "/" << arr[i].word;
        if (i < arr.size() - 1) file << ", ";
    }
    file << "]" << endl;

    file.close(); 
}

//function for partition quick sort
int partition(int start, int end) {
    int pivot = arr[end].number; //last element as the pivot
    int i = start - 1;

    for (int j = start; j < end; j++) {
        if (arr[j].number <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    //place pivot in the correct sorted position
    swap(arr[i + 1], arr[end]);
    return i + 1; 
}

void quickSort(int start, int end, string filename) {
    if (start < end) {
        int pi = partition(start, end);                
        printArrayToFile(filename, pi);               
        quickSort(start, pi - 1, filename); //sort left part
        quickSort(pi + 1, end, filename); //sort right part
    }
}

int main() {
    //prompt user start and end row 
    cout << "Enter starting row: ";
    cin >> startRow;
    cout << "Enter ending row: ";
    cin >> endRow;

    ifstream file("dataset_20000000.csv"); //change filename following the path
    string line;
    int currentLine = 1;

    //read each line and extract data between startRow and endRow 
    while (getline(file, line)) {
        if (currentLine >= startRow && currentLine <= endRow) {
            size_t commaPos = line.find(',');  
            string numPart = line.substr(0, commaPos); //xtract number part
            string wordPart = line.substr(commaPos + 1); //extract word part
            int num = stoi(numPart);//convert number to int

            Data data;
            data.number = num;
            data.word = wordPart;
            arr.push_back(data);                           
        }

        currentLine++;
        if (currentLine > endRow) break;                   
    }

    file.close(); 

    //naming output file
    string filename = "quick_sort_step_" + to_string(startRow) + "_" + to_string(endRow) + ".txt";

    //log array before sorting
    printArrayToFile(filename, -1); //-1 means no pivot yet

    clock_t start = clock(); //start timing
    quickSort(0, arr.size() - 1, filename);
    clock_t end = clock(); //stop timing

    //calculating time duration
    double duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Running time: " << duration << " seconds" << endl;

    return 0;
}
