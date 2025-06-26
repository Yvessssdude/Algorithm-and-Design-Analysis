import csv

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

def format_array(arr):
    return "[" + ", ".join(f"{num}/{string}" for num, string in arr) + "]"

def merge_sort_with_full_tracking(arr, steps, left, right):
    if left < right:
        mid = (left + right) // 2
        merge_sort_with_full_tracking(arr, steps, left, mid)
        merge_sort_with_full_tracking(arr, steps, mid + 1, right)
        merge(arr, steps, left, mid, right)

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

    # ✅ Log the full array only after each full merge
    steps.append(format_array(arr))

def write_steps_to_file(filename, steps):
    with open(filename, 'w') as f:
        for step in steps:
            f.write(step + "\n")

def main():
    input_file = 'dataset_1000.csv'
    all_data = read_dataset(input_file)
    total_rows = len(all_data)

    try:
        start = int(input(f"Enter start row (1 to {total_rows}): ")) - 1
        end = int(input(f"Enter end row ({start+1} to {total_rows}): "))
    except ValueError:
        print("Please enter valid integers.")
        return

    if start < 0 or end > total_rows or start >= end:
        print("Invalid range.")
        return

    to_sort = all_data[start:end]
    steps = [format_array(to_sort)]
    merge_sort_with_full_tracking(to_sort, steps, 0, len(to_sort) - 1)

    output_file = f"merge_sort_step_{start+1}_{end}.txt"
    write_steps_to_file(output_file, steps)

    print(f"Sorting steps saved to '{output_file}'")

if __name__ == "__main__":
    main()
