import cs50
import csv
from sys import argv

if (len(argv) != 2):
    print("Usage: python import.py <filename.csv>")
    exit(1)


db = cs50.SQL("sqlite:///students.db")

with open(argv[1], "r") as characters:

    reader = csv.DictReader(characters)

    for row in reader:
        name = row["name"].split()
        first = name[0]
        middle = None
        last = name[-1]
        
        if len(name) == 3:
            middle = name[1]

        query = "INSERT INTO students (first, middle, last, house, birth) " +\
            "VALUES(?,?,?,?,?)"

        print ("Adding " + row["name"])
        db.execute(query, first, middle, last, row["house"], row["birth"])


