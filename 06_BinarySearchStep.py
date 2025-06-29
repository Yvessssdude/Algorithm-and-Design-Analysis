import csv


def binarySearchStep(filename, target):
    #read and load the sorted dataset
    data = []
    with open(filename, mode='r', newline='') as file:
        reader = csv.reader(file)
        for row in reader:
            if row and len(row) == 2:
                try:
                    num = int(row[0])
                    data.append((num, row[1]))
                except ValueError:
                    continue

    #binary search and trace every steps
    left = 0
    right = len(data) - 1
    steps = []
    found = False

    while left <= right:
        mid = (left + right) // 2
        current_num, current_str = data[mid]
        steps.append(f"{mid}: {current_num}/{current_str}")

        if current_num == target:
            found = True
            break
        elif current_num < target:
            left = mid + 1
        else:
            right = mid - 1

    if not found:
        steps.append("-1")

    #output file to binary_search_step_(target).txt
    output_file = f"binary_search_step_{target}.txt"
    with open(output_file, 'w') as f:
        for step in steps:
            f.write(step + "\n")

    print(f"Search steps saved to: {output_file}")

#Main
if __name__ == "__main__":
   
    dataSize = input("Enter dataset size : ").strip()
    target = input("Enter target number : ").strip()
    targetNum = int(target)

    dataFile = f"merge_sort_{dataSize}.csv"

    #perform binary search
    binarySearchStep(dataFile, targetNum)
