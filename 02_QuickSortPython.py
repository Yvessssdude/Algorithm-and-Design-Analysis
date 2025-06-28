import csv
import time

# Picking last element as pivot
# Two pointers (i and j) for future swapping
# Left side should be all smaller element, right side should be all larger element (Comparing with pivot)
# General flow: 
# Compare element at index j with pivot value, 
#   if smaller than pivot, i incremented, i and j swapped, j incremented 
#   else no change, j incremented, comparing next element
#   At the end swap element at index i+1 with pivot 
#   return the current pivot position (partition index)

def partition(A, start, end, sortPrior):
    pivot = A[end][sortPrior]
    i = start - 1

    for j in range(start, end):
        if A[j][sortPrior] <= pivot:
            i += 1
            A[i], A[j] = A[j], A[i]

    A[i + 1], A[end] = A[end], A[i + 1]
    return i + 1


# Calling recursion on each side of the partition to finish up sorting
def quicksort(A,start,end,sortPrior):
    if start<end:
        pivot=partition(A,start,end,sortPrior)
        quicksort(A,start,pivot-1,sortPrior)
        quicksort(A,pivot+1,end,sortPrior)
        

# 0 represent sorting for numbers
def QuicksortNumber(A,start,end):
    quicksort(A,start,end,0)

# usage:
A=[]
datasetSize = int(input("Enter dataset size: ")) 
with open(f"dataset_{datasetSize}.csv", "r") as file:
    reader = csv.reader(file)
    for row in reader:
        A.append([int(row[0]), row[1]])

#Start timer before calling funtion, end timer after finish running
startTimer=time.time()
QuicksortNumber(A,0,len(A)-1)
endTimer=time.time()

# Display run time in seconds
print("Running time: ",endTimer-startTimer, "seconds")

# Saving array in csv file
filename = "quick_sort_" + str(len(A)) + ".csv" 
with open(filename, 'w', newline='') as f:
            writer = csv.writer(f)
            writer.writerows(A)