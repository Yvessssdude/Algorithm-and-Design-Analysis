import csv
import time


#binary search LOGIC FUNCTION
def binarySearch(data, target):

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

#calculate time for each binary search
def calculateTimes(data):
    times = []
    for i in range(len(data)):
        target = data[i][0]
        start = time.perf_counter()
        binarySearch(data, target) #perform binary search
        endTime = time.perf_counter()
        finalTime = (endTime - start) * 1000  #convert to milliseconds
        times.append(finalTime)
    return times

    
#MAIN
def main():

    #prompt the user to enter dataset size
    dataSize = input("Enter dataset size : ").strip()
    dataFile = f"merge_sort_{dataSize}.csv"
    outputFile = f"binary_search_{dataSize}.txt"

    data = []

    #load data from file
    with open(dataFile, mode='r', newline='') as file:
        reader = csv.reader(file)
        for row in reader:
            try:
                num = int(row[0])
                data.append((num, row[1]))
            except (IndexError, ValueError):
                continue  #skip invalid rows

    times = calculateTimes(data) #measure search times

    best = min(times)
    worst = max(times)
    average = sum(times) / len(times)

    with open(outputFile, 'w') as f:
        f.write(f"Best case time   : {best:.4f} ms\n")
        f.write(f"Average case time: {average:.4f} ms\n")
        f.write(f"Worst case time  : {worst:.4f} ms\n")

    print(f"Search time report saved to: {outputFile}")


if __name__ == "__main__":
    main()
