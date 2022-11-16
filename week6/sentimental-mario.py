# TODO
from cs50 import get_int

while True:
    height = get_int("Height: ")
    if height >= 1 and height <= 8:
        break
# print(height)
for i in range(1, height+1): # start counter from 1
    for j in range(height-i):
        print(" ", end="")

    # left side
    for j in range(i):
        print("#", end="")

    # spacing
    print("  ", end="")

    # right side
    for j in range(i):
        print("#", end="")

    print() # finish by printing new line