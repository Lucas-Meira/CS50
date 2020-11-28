from sys import exit

number = input("Number: ")

if len(number) < 13 or len(number) > 16:
    print("INVALID")
    exit(0)

accSum = 0
digitsSum = 0
currentMult = 0

number = number[::-1]

for n in number[1::2]:
    if int(n) not in range(10):
        print("INVALID")
        exit(0)

    currentMult = 2 * int(n)
    currentMult = [int(i) for i in str(currentMult)]
    accSum += sum(currentMult)

for n in number[0::2]:
    if int(n) not in range(10):
        print("INVALID")
        exit(0)

    digitsSum += int(n)

sumNotMult = digitsSum + accSum

number = number[::-1]

if (sumNotMult % 10 != 0):
    print("INVALID")
    exit(0)

elif (number[0] == "4"):
    print("VISA")
    exit(0)

elif (len(number) == 15):
    if (number[:2] in ["34", "37"]):
        print("AMEX")
        exit(0)
    else:
        print("INVALID")
        exit(0)

elif (len(number) == 16):
    if (51 <= int(number[:2]) <= 55):
        print("MASTERCARD")
        exit(0)
    else:
        print("INVALID")
        exit(0)
else:
    print("INVALID")
    exit(0)