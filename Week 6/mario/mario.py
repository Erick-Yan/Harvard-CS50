while True:
    height = input("Height: ")
    if height.isalpha() or len(height) == 0:
        continue
    elif int(height) > 0 and int(height) < 9:
        break
    else:
        continue

for i in range(1, int(height)+1):
    print(' ' * (int(height) - i), end='')
    print('#'*i, "", "#"*i)
