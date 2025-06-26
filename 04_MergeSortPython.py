import csv
import time
import os

# Read all rows from the dataset
def read_dataset(file_path):
    data = []
    with open(file_path, 'r') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            if len(row) == 2:
                try:
                    number = int(row[0])
                    data.append((number, row[1]))
                except ValueError:
                    continue
    return data

# Merge Sort implementation
def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        L = arr[:mid]
        R = arr[mid:]

        merge_sort(L)
        merge_sort(R)

        i = j = k = 0

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

# Write sorted result to a .csv file
def write_to_csv(filename, data):
    with open(filename, 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerows(data)

# Main function
def main():
    input_file = 'dataset_1000000.csv'

    # Extract dataset size from filename
    dataset_size = os.path.splitext(os.path.basename(input_file))[0].split('_')[-1]
    output_file = f"merge_sort_{dataset_size}.csv"

    # Load data
    all_data = read_dataset(input_file)

    # Sort and time only the sorting operation
    start_time = time.perf_counter()
    merge_sort(all_data)
    end_time = time.perf_counter()

    # Save sorted data
    write_to_csv(output_file, all_data)

    # Print timing
    elapsed_ms = (end_time - start_time) * 1000
    print(f"Sorted {len(all_data)} records in {elapsed_ms:.2f} ms")
    print(f"Output saved to '{output_file}'")

if __name__ == "__main__":
    main()
