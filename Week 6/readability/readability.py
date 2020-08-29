text = input("Text: ")

letters = 0;
words = 0;
sentences = 0;

for i in text:
    if i.isalpha() or i.isdigit():
        letters += 1
    elif i.isspace():
        words += 1
    elif i == '.' or i == '!' or i == '?':
        sentences += 1

words = words + 1

L = (100 / words) * letters
S = (100 / words) * sentences
index = round(0.0588 * L - 0.296 * S - 15.8)

if index >= 1 and index < 16:
    print(f"Grade {index}")
elif (index < 1):
    print("Before Grade 1")
elif (index >= 16):
    print("Grade 16+")