import random
import csv
import string
import sys

# Check first if user provide any size of dataset
if len(sys.argv) != 2:
    print("Please run the program like this:")
    print("python 01_DataGenerator.py 1000")
    sys.exit()

# Get dataset size from command 
n = int(sys.argv[1])
filename = "dataset_" + str(n) + ".csv" 

# Create empty list 
numbers = random.sample(range(1, 2000000000), n)

# Open file
file = open(filename, 'w', newline='')
writer = csv.writer(file)

# Write the rows in the file
for i in range(n):
    num = numbers[i]
    str_length = random.randint(4, 6)
    random_string = ""
    for j in range(str_length):
        random_letter = random.choice(string.ascii_lowercase)
        random_string += random_letter
    writer.writerow([num, random_string])

file.close()

print("Dataset with", n, "rows saved as", filename)
