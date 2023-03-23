// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of words
int num_of_words = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *current_node = table[tolower(word[0]) - 'a'];
    while (current_node != NULL)
    {
        if (strcasecmp(current_node->word, word) == 0)
        {
            return true;
        }

        current_node = current_node->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char tmp[LENGTH + 1];
    while (fscanf(file, "%s", tmp) != EOF)
    {
        if (strlen(tmp) > LENGTH)
        {
            continue;
        }
        node *word_node = malloc(sizeof(node));
        if (word_node == NULL)
        {
            fclose(file);
            return false;
        }

        strcpy(word_node->word, tmp);
        int index = hash(word_node->word);
        word_node->next = table[index];
        table[index] = word_node;
        num_of_words += 1;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (num_of_words > 0)
    {
        return num_of_words;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < 26; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        table[i] = NULL;
    }
    return true;
}
