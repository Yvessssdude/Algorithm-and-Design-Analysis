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
# Storing output everytime finish one pertitioning, to record current pivot position and current sort progress
def quicksort(A,start,end,sortPrior,startrow, endrow):
    if start<end:
        pivot=partition(A,start,end,sortPrior)
        StoreOutput(A,pivot,startrow, endrow)
        quicksort(A,start,pivot-1,sortPrior,startrow, endrow)
        quicksort(A,pivot+1,end,sortPrior,startrow, endrow)


# 0 represent sorting for numbers
def QuicksortNumber(A,start,end,startrow, endrow):
    quicksort(A,start,end,0,startrow, endrow)

# Storing new
# General flow: Looping through updated A[0] and reformat data display
# Saving the formatted data in new array
def StoreOutput(A, pi,startrow, endrow):
    formattedArray=[]
    for data in A:
        number = str(data[0])       
        text = data[1]
        combined = f"{number}/{text}"
        formattedArray.append(combined)
        formattedData = ', '.join(formattedArray)
    output_line = f"pi={pi} [{formattedData}]"
    print(output_line)
    filename = "quick_sort_" + str(startrow)+"_"+ str(endrow)  + ".txt"  
    with open(filename, 'a', newline='') as f:
        f.write(output_line + '\n')

# Extracting user requested data row 
# General flow: Looping through A[0] and reformat data display
# Saving the formatted data in new array
def freshOutput(A, formattedArray,startrow, endrow):
    for data in A:
        number = str(data[0])       
        text = data[1]
        combined = f"{number}/{text}"
        formattedArray.append(combined)
    formattedData = ', '.join(formattedArray)
    output_line = f"[{formattedData}]"
    filename = "quick_sort_" + str(startrow)+"_"+ str(endrow)  + ".txt" 
    with open(filename, 'w', newline='') as f:
            f.write(output_line + '\n')

        

# usage:
A=[]
formattedArray=[]
startRow = int(input("Enter starting row: "))  
endRow = int(input("Enter ending row: "))  
datasetSize = int(input("Enter dataset size: ")) 
with open(f"dataset_{datasetSize}.csv", "r", newline='') as file:
    reader = csv.reader(file)
    for line_number, row in enumerate(reader, start=1):
        if startRow <= line_number <= endRow:
            A.append([int(row[0]), row[1]])
            print(A)
        elif line_number > endRow:
            break

# freshOutput purpose: extracting requested data that has not been processed
startTimer=time.time()
freshOutput(A,formattedArray,startRow, endRow)
QuicksortNumber(A,0,len(A)-1,startRow, endRow)
endTimer=time.time()
