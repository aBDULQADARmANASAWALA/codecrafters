text = input("Text: ")
words = 1
letters = 0
sentences = 0

for c in text:
    if c.isalpha():
        letters += 1
    elif c in ['!', '.', '?']:
        sentences += 1
    elif c in [' ', '\\n', '\\t']:
        words += 1

L = letters / words * 100
S = sentences / words * 100
grade = 0.0588 * L - 0.296 * S - 15.8

if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print("Grade " + str(round(grade)))
