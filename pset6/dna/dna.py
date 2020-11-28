from sys import argv, exit
import csv

if (len(argv) != 3):
    print("Usage: python dna.py data.csv sequence.txt")
    exit()

# Open CSV file
csvfile = open(argv[1], "r") 
data = csv.DictReader(csvfile) 

# Init dictionary
strCount = {}

with open(argv[2], "r") as sequences:
    sequence = sequences.read()

    for STR in data.fieldnames[1:]:        
        occurrences = []
        
        # Copy sequence into string to be modified
        modifiedSequence = sequence

        while True:
            # Find first occurrence
            position = modifiedSequence.find(STR)

            # If we find an occurrence
            if (position >= 0):
                # Keep only the rest of the sequence
                modifiedSequence = modifiedSequence[position  + len(STR):]

                occurrences.append(1)
            else:
                break
            
            # While the occurrence happens right after the last one, we increment the occurrences variable
            while (modifiedSequence.find(STR) == 0):
                occurrences[len(occurrences) - 1] += 1
                modifiedSequence = modifiedSequence[len(STR):]

        # Find longest occurrence and store into the dictionnary
        strCount[STR] = max(occurrences)


matchCount = 0

# Compare to each person in the CSV file
for row in data:
    for STR in data.fieldnames[1:]:
        if (int(row[STR]) == strCount[STR]):
            matchCount += 1
        else:
            break
        
        # Print and exit if STR counts match exactly
        if (matchCount == len(data.fieldnames) - 1):
            print(row["name"])
            exit(0)

    matchCount = 0

print("No match")