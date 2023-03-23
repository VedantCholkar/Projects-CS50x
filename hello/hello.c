#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string user_name = get_string("What is you name?\n"); // Gets user's name
    printf("hello, %s\n", user_name); // Prints hello, user's name
}