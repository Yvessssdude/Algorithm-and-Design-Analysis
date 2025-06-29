import csv
import time



# Merge Sort with index tracking for in-place sorting
def mergeSort(arr, left, right):
    if left < right:
        mid = (left + right) // 2
        mergeSort(arr, left, mid)
        mergeSort(arr, mid + 1, right)
        merge(arr, left, mid, right)

def merge(arr, left, mid, right):
    L = arr[left:mid + 1]
    R = arr[mid + 1:right + 1]

    i = j = 0
    k = left

    while i < len(L) and j < len(R):
        if L[i][0] < R[j][0]:
            arr[k] = L[i]
            i += 1
        else:
            arr[k] = R[j]
            j += 1
        k += 1

    while i < len(L):
        arr[k] = L[i]
        i += 1
        k += 1

    while j < len(R):
        arr[k] = R[j]
        j += 1
        k += 1

    
#MAIN
def main():

    dataSize = input("Enter dataset size : ").strip()
    dataFile = f"dataset_{dataSize}.csv"
    outputFile = f"merge_sort_{dataSize}.csv"

    #read and load data 
    data = []
    with open(dataFile, 'r') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            if len(row) == 2:
                try:
                    number = int(row[0])
                    data.append((number, row[1]))
                except ValueError:
                    continue

    #sort and time only the sorting operation
    start = time.perf_counter()
    mergeSort(data, 0, len(data) - 1)
    endTime = time.perf_counter()

    #save sorted data in output file
    with open(outputFile, 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerows(data)

    #print running time
    elapsed_sec = endTime - start
    print(f"Sorted {len(data)} records in {elapsed_sec:.2f} seconds")
    print(f"Output saved to '{outputFile}'")

if __name__ == "__main__":
    main()
