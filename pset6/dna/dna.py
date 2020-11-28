from sys import argv
import csv

if (len(argv) != 3):
    print("Usage: python dna.py data.csv sequence.txt")

data = csv.reader(argv[1], "r")
sequence = open(argv[2], "r")

for row in data:
    