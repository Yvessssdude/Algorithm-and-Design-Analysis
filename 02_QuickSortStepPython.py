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


def quicksort(A,start,end,sortPrior,startrow, endrow):
    if start<end:
        pivot=partition(A,start,end,sortPrior)
        StoreOutput(A,pivot,startrow, endrow)
        quicksort(A,start,pivot-1,sortPrior,startrow, endrow)
        quicksort(A,pivot+1,end,sortPrior,startrow, endrow)
        

def QuicksortString(A,start,end,startrow, endrow):
    quicksort(A,start,end,1,startrow, endrow)

def QuicksortNumber(A,start,end,startrow, endrow):
    quicksort(A,start,end,0,startrow, endrow)

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
    filename = "quick_sort_" + str(startrow)+"_"+ str(endrow)  + ".csv"  
    with open(filename, 'a', newline='') as f:
        f.write(output_line + '\n')

def freshOutput(A, formattedArray,startrow, endrow):
    for data in A:
        number = str(data[0])       
        text = data[1]
        combined = f"{number}/{text}"
        formattedArray.append(combined)
    formattedData = ', '.join(formattedArray)
    output_line = f"[{formattedData}]"
    filename = "quick_sort_" + str(startrow)+"_"+ str(endrow)  + ".csv" 
    with open(filename, 'w', newline='') as f:
            f.write(output_line + '\n')

        

# usage:
A=[]
formattedArray=[]
startRow = int(input("Enter starting row: "))  
endRow = int(input("Enter ending row: "))  

with open("dataset_1000.csv", "r", newline='') as file:
    reader = csv.reader(file)
    for line_number, row in enumerate(reader, start=1):
        if startRow <= line_number <= endRow:
            A.append([int(row[0]), row[1]])
            print(A)
        elif line_number > endRow:
            break

startTimer=time.time()
freshOutput(A,formattedArray,startRow, endRow)

QuicksortNumber(A,0,len(A)-1,startRow, endRow)
#QuicksortString(A,0,len(A)-1)

endTimer=time.time()
print("Running time: ",endTimer-startTimer, "seconds")