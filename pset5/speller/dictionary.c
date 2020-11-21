// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
static const unsigned int N = 26U;

// Hash table
node *table[N];

char toLower(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return c;
    }

    return c + 32;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int hashValue = 0;
    char lowerWord[LENGTH + 1];
    int index = 0;

    strcpy(lowerWord, word);

    while (lowerWord[index] != '\0')
    {
        lowerWord[index] = toLower(lowerWord[index]);

        index++;
    }

    hashValue = hash(lowerWord);

    node *tmp = table[hashValue];

    if (NULL == tmp)
    {
        return false;
    }

    if (NULL == tmp->next)
    {
        if (strcmp(lowerWord, tmp->word) == 0)
        {
            return true;
        }

        return false;
    }

    while (tmp->next != NULL)
    {
        if (strcmp(lowerWord, tmp->word) == 0)
        {
            return true;
        }

        tmp = tmp->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hashValue = 0;

    hashValue = *word - 'a';

    printf("%d\n", hashValue);

    return hashValue;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        return false;
    }

    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH + 1];
    node *item = malloc(sizeof(node));



    for (int c = fgetc(file); c != EOF; c = fgetc(file))
    {
        if ('\n' == c)
        {
            word[index] = '\0';
            index = 0;

            unsigned int hashValue = hash(word);

            if (NULL == table[hashValue])
            {
                table[hashValue] = item;
            }
            else
            {
                node *tmp = table[hashValue];

                while (NULL != tmp->next)
                {
                    tmp = tmp->next;
                }

                strcpy(item->word, word);
                item->next = NULL;

                tmp = item;
            }
        }
        else
        {
            word[index] = c;
            index++;
        }
    }

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
