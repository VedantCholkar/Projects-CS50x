// The code is the documentation
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool only_digits(string input);
char encrypt(char input, int key);

int main(int argc, string argv[])
{
    if (argc != 2 || only_digits(argv[1]) == false) // Validates input
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int key = atoi(argv[1]); // Converts input to integer
    string plaintext = get_string("plaintext: ");
    string ciphertext = "";
    printf("ciphertext: ");
    for (int i = 0, j = strlen(plaintext); i < j; i++) // Uses encrypt function to rotate characters
    {
        printf("%c", encrypt(plaintext[i], key));
    }
    printf("\n");
    return 0;
}

bool only_digits(string input) // Allows only digits as input
{
    for (int i = 0, j = strlen(input); i < j; i++)
    {
        if (isdigit(input[i]))
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

char encrypt(char input, int key) // Rotates characters
{

    if (isalpha(input)) // Checks if input is a charater in the alphabet
    {
        char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
        int upper = 0; // Keeps tab of if input is uppercase
        if (islower(input))
        {
            input -= 97;
        }
        else if (isupper(input))
        {
            input -= 65;
            upper = 1; // Original character is uppercase
        }
        input += key; // Adds key to character
        input = input % 26; // Makes sure the character wraps around the alphabet
        unsigned char x = input; // Fixed error of *array subscript is of type 'char'*
        input = alphabet[x];
        if (upper == 1) // Converts to uppercase
        {
            input = toupper(input);
        }
    }
    return input;
}