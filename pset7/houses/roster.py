import cs50
from sys import argv

if (len(argv) != 2):
    print("Usage: python roster.py <roster>")
    exit(1)

roster = argv[1].upper()

db = cs50.SQL("sqlite:///students.db")

query = "SELECT * FROM students WHERE UPPER(house) LIKE \"" + roster + "\""

response = db.execute(query)

for student in sorted(response, key=lambda item: item["last"]):

    print(student["first"], end=" ")

    if (student["middle"] != None):
        print(student["middle"], end=" ")
    
    print(student["last"], end=", ")

    print("born " + str(student["birth"]))
