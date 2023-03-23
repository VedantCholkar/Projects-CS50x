#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();
    // printf("%i\n", cents);

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;
    // printf("%i\n", cents);

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;
    // printf("%i\n", cents);

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;
    // printf("%i\n", cents);

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;
    // printf("%i\n", cents);

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;
    // printf("%i\n", cents);

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    int user_input = 0;
    do
    {
        user_input = get_int("Change owed: ");
    }
    while (user_input < 0);
    return user_input;
}

int calculate_quarters(int cents)
{
    int quarters_needed = 0;
    while (cents >= 25)
    {
        cents -= 25;
        quarters_needed += 1;
    }
    return quarters_needed;
}

int calculate_dimes(int cents)
{
    int dimes_needed = 0;
    while (cents >= 10)
    {
        cents -= 10;
        dimes_needed += 1;
    }
    return dimes_needed;
}

int calculate_nickels(int cents)
{
    int nickels_needed = 0;
    while (cents >= 5)
    {
        cents -= 5;
        nickels_needed += 1;
    }
    return nickels_needed;
}

int calculate_pennies(int cents)
{
    int pennies_needed = 0;
    while (cents >= 1)
    {
        cents -= 1;
        pennies_needed += 1;
    }
    return pennies_needed;
}
