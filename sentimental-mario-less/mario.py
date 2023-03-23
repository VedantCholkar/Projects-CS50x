from cs50 import get_int

while True:  # Forever loop
    height = get_int("Height: ")
    if (height > 0 and height < 9):  # Validates input
        break

for i in range(height):
    print(" " * ((height - 1) - i), end="")  # Calculates how many spaces needed
    print("#" * (i + 1), end="")  # Prints hashes