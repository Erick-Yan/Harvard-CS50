while True:
    cred = input("Number: ")
    if cred.isalpha() or len(cred) == 0:
        continue
    elif len(cred) > 12 and len(cred) < 17 and len(cred) != 14:
        break
    else:
        print("INVALID")
        exit(1)

second = cred[-2::-2]
first = cred[-1::-2]
next1 = []
sum = 0;

for i in second:
    a = str(int(i)*2)
    for j in a:
        next1.append(j)

for k in next1:
    sum += int(k)

for l in first:
    sum += int(l)

if sum % 10 == 0:
    if len(cred) == 13 and cred[0] == '4':
        print("VISA")
    elif len(cred) == 15 and cred[0:2] == '34' or cred[0:2] == '37':
        print("AMEX")
    elif len(cred) == 16 and cred[0:2] == '51' or cred[0:2] == '52' or cred[0:2] == '53' or cred[0:2] == '54' or cred[0:2] == '55':
        print("MASTERCARD")
    elif len(cred) == 16 and cred[0] == '4':
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")

