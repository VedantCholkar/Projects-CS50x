#include <cs50.h>
#include <stdio.h>

int main(void)
{

    int user_input = 0;
    do
    {
        user_input = get_int("Height: "); // gets user input
    }
    while (user_input < 1 || user_input > 8); // only accepts integer 1-8

    for (int rows_left = 0; rows_left < user_input; rows_left++) // calculates rows
    {
        for (int columns_finished = rows_left + 1; columns_finished < user_input; columns_finished++) // calculates spaces in first pyramid
        {
            printf(" ");
        }
        for (int colums_left = 0; colums_left < rows_left + 1; colums_left++) // calculates hashes in first pyramid
        {
            printf("#");
        }
        printf("  "); // adds a space between the 2 pyramids
        for (int colums_left2 = 0; colums_left2 < rows_left + 1; colums_left2++) // calculates hashs in second pyramid
        {
            printf("#");
        }
        printf("\n"); // newline after row finished
    }
}