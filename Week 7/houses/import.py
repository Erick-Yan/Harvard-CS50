from cs50 import SQL
import csv
from sys import argv

if len(argv) != 2:
    print("Need More Arguments")
    exit(1)

open("students.db", "w").close()
db = SQL("sqlite:///students.db")
db.execute("CREATE TABLE students(first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC)")

with open(argv[1], "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        name_split = row['name'].split(" ")
        if len(name_split) == 2:
            tmp = name_split[1]
            name_split[1] = None
            name_split.append(tmp)
        db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", name_split[0], name_split[1], name_split[2], row['house'], row['birth'])
        #print(row['birth'])


