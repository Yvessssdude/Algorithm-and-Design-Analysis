import csv
import sys
import os

def binary_search_step(filename, target):
    # Read and load the sorted dataset
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

    # Binary search and trace steps
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

    # Output to required file format
    output_file = f"binary_search_step_{target}.txt"
    with open(output_file, 'w') as f:
        for step in steps:
            f.write(step + "\n")

    print(f"Search steps saved to: {output_file}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python binary_search_step.py <sorted_dataset.csv> <target_integer>")
        sys.exit(1)

    dataset_file = sys.argv[1]
    try:
        target_value = int(sys.argv[2])
    except ValueError:
        print("Error: target must be an integer.")
        sys.exit(1)

    if not os.path.exists(dataset_file):
        print(f"File not found: {dataset_file}")
        sys.exit(1)

    binary_search_step(dataset_file, target_value)
