import csv
import time

def partition(A, l, h,sortPrior):
    pivot = A[l][sortPrior]
    i = l
    j = h

    while i < j:
        while i < h and A[i][sortPrior] <= pivot:
            i += 1
        while A[j][sortPrior] > pivot:
            j -= 1
        if i < j:
            A[i], A[j] = A[j], A[i]

    A[l], A[j] = A[j], A[l]
    return j

def quicksort(A, l, h, sortBy):
    sortPrior=sortBy
    if l < h:
        j = partition(A, l, h,sortPrior)
        quicksort(A, l, j - 1,sortPrior)
        quicksort(A, j + 1, h,sortPrior)
        

def QuicksortString(A,l,h):
    quicksort(A,l,h,1)

def QuicksortNumber(A,l,h):
    quicksort(A,l,h,0)

# usage:
A=[]
with open("dataset_10000000.csv", "r") as file:
    reader = csv.reader(file)
    for row in reader:
        A.append([int(row[0]), row[1]])

startTimer=time.time()
QuicksortNumber(A,0,len(A)-1)
#QuicksortString(A,0,len(A)-1)

endTimer=time.time()
print("Running time: ",endTimer-startTimer, "seconds")

filename = "quick_sort_" + str(len(A)) + ".csv" 
with open(filename, 'w', newline='') as f:
            writer = csv.writer(f)
            writer.writerows(A)


        
