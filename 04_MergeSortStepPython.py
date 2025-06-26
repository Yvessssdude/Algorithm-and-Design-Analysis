import csv

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

# Convert array to output string format
def format_array(arr):
    return "[" + ", ".join(f"{num}/{string}" for num, string in arr) + "]"

# Merge Sort with step tracking
def merge_sort(arr, steps):
    if len(arr) > 1:
        mid = len(arr) // 2
        L = arr[:mid]
        R = arr[mid:]

        merge_sort(L, steps)
        merge_sort(R, steps)

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

        # Save snapshot after merge
        steps.append(format_array(arr))

# Write step snapshots to file
def write_steps_to_file(filename, steps):
    with open(filename, 'w') as f:
        for step in steps:
            f.write(step + "\n")

# Main function
def main():
    input_file = 'dataset_1000.csv'

    all_data = read_dataset(input_file)
    total_rows = len(all_data)

    # Get user input for row range
    try:
        start = int(input(f"Enter start row (1 to {total_rows}): ")) - 1
        end = int(input(f"Enter end row ({start+1} to {total_rows}): "))
    except ValueError:
        print("Please enter valid integers for row indices.")
        return

    # Validate input
    if start < 0 or end > total_rows or start >= end:
        print("Invalid range. Please ensure 0 <= start < end <= total rows.")
        return

    # Extract range and sort with step logging
    to_sort = all_data[start:end]
    steps = [format_array(to_sort)]  # Initial unsorted state
    merge_sort(to_sort, steps)

    # Output to required format
    output_file = f"merge_sort_step_{start+1}_{end}.txt"
    write_steps_to_file(output_file, steps)

    print(f"Sorting steps from line {start+1} to {end} saved in '{output_file}'.")

if __name__ == "__main__":
    main()
