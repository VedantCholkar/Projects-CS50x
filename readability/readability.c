#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    float num_of_letters = count_letters(text);
    float num_of_words = count_words(text);
    float num_of_sentences = count_sentences(text);
    float L = num_of_letters / num_of_words * 100;
    float S = num_of_sentences / num_of_words * 100;
    int reading_level = round(0.0588 * L - 0.296 * S - 15.8);
    if (reading_level < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (reading_level >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", reading_level);
    }
}

int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, l = strlen(text); i < l; i++) // Goes through each character in given text
    {
        if (isalpha(text[i])) // Checks if current character is a letter
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string text)
{
    int words = 1; // Assumes a sentence has at least 1 word
    for (int i = 0, l = strlen(text); i < l; i++) // Goes through each character in given text
    {
        if (text[i] == 32) // Checks if the current character is a space
        {
            words++;
        }
    }
    return words;
}

int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0, l = strlen(text); i < l; i++) // Goes through each character in given text
    {
        if (text[i] == 46 || text[i] == 33 || text[i] == 63) // Checks if current character is "." or "!" or "?"
        {
            sentences++;
        }
    }
    return sentences;
}