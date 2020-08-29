from cs50 import SQL
import csv
from sys import argv

if len(argv) != 2:
    print("Need More Arguments")
    exit(1)

file = open("students.db", "r")
db = SQL("sqlite:///students.db")
raq = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last ASC, first", argv[1])

for i in raq:
    if i['middle'] == None:
        print("{} {}, born {}".format(i['first'], i['last'], i['birth']))
    else:
        print("{} {} {}, born {}".format(i['first'], i['middle'], i['last'], i['birth']))
