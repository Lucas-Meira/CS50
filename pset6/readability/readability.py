text = input("Text: ")

text = text.split()

W = len(text)

S = 0
L = 0

for word in text:

    L += len(word)

    if word.find('\'') != -1:
        L -= 1


    if word[-1] in ["!", "?", "."]:
        S += 1
        L -= 1

grade = 100 * 0.0588 * L / W - 0.296 * 100 * S / W - 15.8

if (grade < 1):
    print ("Before Grade 1")

elif (grade > 16):
    print ("Grade 16+")

else:
    print ("Grade " + str(round(grade)))