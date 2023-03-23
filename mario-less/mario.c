#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int user_input = 0;
    do
    {
        user_input = get_int("Height: "); // gets user input
    }
    while (user_input < 1 || user_input > 8); // does not accept anthing other than integer 1-8

    for (int rows_left = 0; rows_left < user_input; rows_left++) // calculates the rows left
    {
        for (int columns_finished = rows_left + 1; columns_finished < user_input; columns_finished++) // calculates the spaces
        {
            printf(" ");
        }
        for (int colums_left = 0; colums_left < rows_left + 1; colums_left++) // calculates the hashes
        {
            printf("#");
        }
        printf("\n");
    }
}