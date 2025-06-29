import csv

#format array for each step
def format_array(arr):
    return "[" + ", ".join(f"{num}/{string}" for num, string in arr) + "]"

#sorting function
def mergeSort(arr, steps, left, right):
    if left < right:
        mid = (left + right) // 2
        mergeSort(arr, steps, left, mid)
        mergeSort(arr, steps, mid + 1, right)
        merge(arr, steps, left, mid, right)

#merge
def merge(arr, steps, left, mid, right):
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

    #log the full array only after each full merge
    steps.append(format_array(arr))


def main():

    dataSize = input("Enter dataset size : ").strip()
    dataFile = f"dataset_{dataSize}.csv"
    data = []
    #read and load data
    with open(dataFile, 'r') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            if len(row) == 2:
                try:
                    number = int(row[0])
                    data.append((number, row[1]))
                except ValueError:
                    continue

    #prompt start and end row
    try:
        start = int(input(f"Enter start row (1 to {dataSize}): ")) - 1
        end = int(input(f"Enter end row ({start+1} to {dataSize}): "))
    except ValueError:
        print("Please enter valid integers.")
        return


    to_sort = data[start:end]
    #print array to be sort
    steps = [format_array(to_sort)]
    #perform sorting
    mergeSort(to_sort, steps, 0, len(to_sort) - 1)

    outputFile = f"merge_sort_step_{start+1}_{end}.txt"

    #print step in file
    with open(outputFile, 'w') as f:
        for step in steps:
            f.write(step + "\n")

    print(f"Sorting steps saved to '{outputFile}'")

if __name__ == "__main__":
    main()
