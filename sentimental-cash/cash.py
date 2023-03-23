from cs50 import get_float

while True:  # Prompts the user for change
    change = get_float("Change: ")
    if (change > 0):
        change = round(change * 100)
        break


def quarters(change):  # Finds the number of quarters
    quarters = 0
    while change >= 25:
        change -= 25
        quarters += 1
    return quarters


def dimes(change):  # Finds the number of dimes
    dimes = 0
    while change >= 10:
        change -= 10
        dimes += 1
    return dimes


def nickels(change):  # Finds the number of nickels
    nickels = 0
    while change >= 5:
        change -= 5
        nickels += 1
    return nickels


def pennies(change):  # Finds the number of pennies
    pennies = 0
    while change >= 1:
        change -= 1
        pennies += 1
    return pennies


# Adds each coin into a variable and updates the change
quarters = quarters(change)
change -= quarters * 25

dimes = dimes(change)
change -= dimes * 10

nickels = nickels(change)
change -= nickels * 5

pennies = pennies(change)
change -= pennies * 1

coins = quarters + dimes + nickels + pennies  # All coins added

print(coins)  # Prints coins needed to pay change
