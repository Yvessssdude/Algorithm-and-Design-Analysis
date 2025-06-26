import csv
import time
import sys
import os

def load_dataset(filename):
    data = []
    with open(filename, mode='r', newline='') as file:
        reader = csv.reader(file)
        for row in reader:
            try:
                num = int(row[0])
                data.append((num, row[1]))
            except (IndexError, ValueError):
                continue  # Skip invalid rows
    return data

def binary_search(data, target):
    left = 0
    right = len(data) - 1
    while left <= right:
        mid = (left + right) // 2
        current = data[mid][0]
        if current == target:
            return mid
        elif current < target:
            left = mid + 1
        else:
            right = mid - 1
    return -1

def measure_search_times(data):
    times = []
    for i in range(len(data)):
        target = data[i][0]
        start_time = time.perf_counter()
        binary_search(data, target)
        end_time = time.perf_counter()
        elapsed_ms = (end_time - start_time) * 1000  # Convert to milliseconds
        times.append(elapsed_ms)
    return times

def save_results(filename, times):
    best = min(times)
    worst = max(times)
    average = sum(times) / len(times)

    with open(filename, 'w') as f:
        f.write(f"Best case time   : {best:.4f} ms\n")
        f.write(f"Average case time: {average:.4f} ms\n")
        f.write(f"Worst case time  : {worst:.4f} ms\n")

    print(f"Search time report saved to: {filename}")

def main():
    if len(sys.argv) != 2:
        print("Usage: python binary_search_large.py <sorted_dataset.csv>")
        sys.exit(1)

    dataset_file = sys.argv[1]

    if not os.path.exists(dataset_file):
        print(f"File not found: {dataset_file}")
        sys.exit(1)

    try:
        dataset_size = os.path.splitext(os.path.basename(dataset_file))[0].split('_')[-1]
    except:
        dataset_size = "output"

    output_file = f"binary_search_{dataset_size}.txt"

    data = load_dataset(dataset_file)
    print(f"Dataset loaded: {len(data)} entries")

    search_times = measure_search_times(data)
    save_results(output_file, search_times)

if __name__ == "__main__":
    main()
