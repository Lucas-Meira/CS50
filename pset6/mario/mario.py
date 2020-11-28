flag = True

while (flag):
    try:
        height = int(input("Height: "))
        if (1 <= height <= 8):
            flag = False
    except:
        pass

for i in range(1, height + 1):
    print(" " * (height - i) + "#" * i, end="")
    print("  ", end="")
    print("#" * i + " " * (height - i))
