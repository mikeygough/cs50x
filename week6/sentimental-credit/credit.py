# TODO
from cs50 import get_int, get_string

# prompt user for cc number
while True:
    cc = get_string("Number: ")
    if len(cc) >= 13 or len(cc) <= 16:
        break

# print("cc:", cc)

# store card length
cc_length = len(cc)

nums_x = []
if (cc_length % 2 == 0):  # if even
    for i in range(-2, len(cc)-2, 2):
        nums_x.append(cc[i])
else:  # if odd
    for i in range(-2, -len(cc), -2):
        nums_x.append(cc[i])

# print("nums_x: ", nums_x)

nums_x_2 = [int(x) for x in nums_x]
nums_x_2 = [x * 2 for x in nums_x_2]
nums_x_2 = [str(x) for x in nums_x_2]

# print("nums_x_2: ", nums_x_2)

sum_x = 0
for num in nums_x_2:
    for d in num:
        sum_x += int(d)

# print("sum_x: ", sum_x)

nums_y = []
if (cc_length % 2 == 0):  # if even
    for i in range(-1, len(cc)-2, 2):
        nums_y.append(int(cc[i]))
else:  # if odd
    for i in range(-1, -len(cc)-1, -2):
        nums_y.append(int(cc[i]))

# print("nums_y: ", nums_y)

# add y numbers to x numbers
for y in nums_y:
    sum_x += y

# print("sum_x (TOTAL): ", sum_x)

# check if valid cc #
if (sum_x % 10 == 0):
    valid = True
else:
    valid = False

# if the total's last digit is 0, the number is valid!
cc_int = [int(x) for x in cc]

# print(cc_length)
# print(valid)

# check card number against criteria for each card
if (cc_length == 15 and cc[0] == "3" and cc[1] == "4" and valid):
    print("AMEX\n", end="")
elif (cc_length == 15 and cc[0] == "3" and cc[1] == "7" and valid):
    print("AMEX\n", end="")
elif (cc_length == 16 and cc[0] == "5" and cc[1] == "1" and valid):
    print("MASTERCARD\n", end="")
elif (cc_length == 16 and cc[0] == "5" and cc[1] == "2" and valid):
    print("MASTERCARD\n", end="")
elif (cc_length == 16 and cc[0] == "5" and cc[1] == "3" and valid):
    print("MASTERCARD\n", end="")
elif (cc_length == 16 and cc[0] == "5" and cc[1] == "4" and valid):
    print("MASTERCARD\n", end="")
elif (cc_length == 16 and cc[0] == "5" and cc[1] == "5" and valid):
    print("MASTERCARD\n", end="")
elif (cc_length == 13 and cc[0] == "4" and valid):
    print("VISA\n", end="")
elif (cc_length == 16 and cc[0] == "4" and valid):
    print("VISA\n", end="")
else:
    print("INVALID\n", end="")
