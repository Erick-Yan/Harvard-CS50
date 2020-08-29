from sys import argv
import csv

while True:
    if len(argv) != 3:
        print("")
        continue
    else:
        break

if argv[1] == 'databases/small.csv':
    file1 = open(argv[1], "r")
    reader1 = csv.DictReader(file1)
    thecsv = dict()
    for row in reader1:
        thecsv[row['name']] = [row['AGATC'], row['AATG'], row['TATC']]
else:
    file1 = open(argv[1], "r")
    reader1 = csv.DictReader(file1)
    thecsv = dict()
    for row in reader1:
        thecsv[row['name']] = [row['AGATC'], row['TTTTTTCT'], row['AATG'], row['TCTAG'], row['GATA'], row['TATC'], row['GAAA'], row['TCTG']]

file2 = open(argv[2], "r")
reader2 = csv.reader(file2, delimiter=' ')
seq = ''
for row2 in reader2:
    seq = row2[0]

tmp1 = 0
aga = [0]
aat = [0]
tat = [0]

tcta = []
gat = []
gaa = []
tct = []
ttt = []
for i in range(len(seq)):
    tmp1 = 0
    if seq[i:i+8] == 'TTTTTTCT':
        tmp1 += 1
        for j in range(i+8, len(seq), 8):
            if seq[j:j+8] == 'TTTTTTCT':
                tmp1 += 1
            else:
                ttt.append(tmp1)
                tmp1 = 0
                break

    if seq[i:i+5] == 'AGATC':
        tmp1 += 1
        for j in range(i+5, len(seq), 5):
            if seq[j:j+5] == 'AGATC':
                tmp1 += 1
            else:
                aga.append(tmp1)
                tmp1 = 0
                break

    elif seq[i:i+5] == 'TCTAG':
        tmp1 += 1
        for j in range(i+5, len(seq), 5):
            if seq[j:j+5] == 'TCTAG':
                tmp1 += 1
            else:
                tcta.append(tmp1)
                tmp1 = 0
                break

    elif seq[i:i+4] == 'AATG':
        tmp1 += 1
        for j in range(i+4, len(seq), 4):
            if seq[j:j+4] == 'AATG':
                tmp1 += 1
            else:
                aat.append(tmp1)
                tmp1 = 0
                break

    elif seq[i:i+4] == 'TATC':
        tmp1 += 1
        for j in range(i+4, len(seq), 4):
            if seq[j:j+4] == 'TATC':
                tmp1 += 1
            else:
                tat.append(tmp1)
                tmp1 = 0
                break

    elif seq[i:i+4] == 'GATA':
        tmp1 += 1
        for j in range(i+4, len(seq), 4):
            if seq[j:j+4] == 'GATA':
                tmp1 += 1
            else:
                gat.append(tmp1)
                tmp1 = 0
                break

    elif seq[i:i+4] == 'GAAA':
        tmp1 += 1
        for j in range(i+4, len(seq), 4):
            if seq[j:j+4] == 'GAAA':
                tmp1 += 1
            else:
                gaa.append(tmp1)
                tmp1 = 0
                break

    elif seq[i:i+4] == 'TCTG':
        tmp1 += 1
        for j in range(i+4, len(seq), 4):
            if seq[j:j+4] == 'TCTG':
                tmp1 += 1
            else:
                tct.append(tmp1)
                tmp1 = 0
                break

    else:
        continue

if argv[1] == 'databases/small.csv':
    check = [str(max(aga)), str(max(aat)), str(max(tat))]
else:
    check = [str(max(aga)), str(max(ttt)), str(max(aat)), str(max(tcta)), str(max(gat)), str(max(tat)), str(max(gaa)), str(max(tct))]
#print(check)

for name, rest in thecsv.items():
    if rest == check:
        print(name)
        exit(1)
    else:
        continue
print('No Match')
#print(thecsv['Lavender'])