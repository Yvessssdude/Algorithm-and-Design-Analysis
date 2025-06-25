import csv
import time

def partition(A, start, end, sortPrior):
    pivot = A[end][sortPrior]
    i = start - 1

    for j in range(start, end):
        if A[j][sortPrior] <= pivot:
            i += 1
            A[i], A[j] = A[j], A[i]

    A[i + 1], A[end] = A[end], A[i + 1]
    return i + 1


def quicksort(A,start,end,sortPrior):
    if start<end:
        pivot=partition(A,start,end,sortPrior)
        quicksort(A,start,pivot-1,sortPrior)
        quicksort(A,pivot+1,end,sortPrior)
        

def QuicksortString(A,start,end):
    quicksort(A,start,end,1)

def QuicksortNumber(A,start,end):
    quicksort(A,start,end,0)

# usage:
A=[]
with open("lectureSample.csv", "r") as file:
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