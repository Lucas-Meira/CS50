// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "dictionary.h"

// Number of buckets in hash table
static const unsigned int N = 26U;

// Hash table
node *table[N];
node *last[N];

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
#ifdef DEBUG
printf("[CHECK] %s\n", tmp->word);
#endif
        if (strcmp(lowerWord, tmp->word) == 0)
        {
            return true;
        }

        return false;
    }

    while (1)
    {
#ifdef DEBUG
        printf("[CHECK] %s\n", tmp->word);
#endif
        if (strcmp(lowerWord, tmp->word) == 0)
        {
            return true;
        }

        if (NULL == tmp->next)
        {
            break;
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
#ifdef DEBUG
    printf("[HASH] %d\n", hashValue);
#endif
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

    for (size_t i = 0; i < N; i++)
    {
        last[i] = table[i];
    }

    char word[LENGTH + 1];

    while (NULL != fgets(word, LENGTH, file))
    {
        // Remove \n
        word[strlen(word)] = '\0';
        node *item = malloc(sizeof(node));

        unsigned int hashValue = hash(word);

        if (NULL == table[hashValue])
        {
            strcpy(item->word, word);
            item->next = NULL;

            table[hashValue] = item;
#ifdef DEBUG
            printf("[LOAD] %s, %p\n", table[hashValue]->word, table[hashValue]->next);
#endif
        }
        else
        {
#ifdef DEBUG
            printf("[LOAD] %s, %p\n", tmp->word, tmp->next);
#endif


            strcpy(item->word, word);
            item->next = NULL;

            last[hashValue]->next = item;

            last[hashValue] = last[hashValue]->next
#ifdef DEBUG
            printf("[LOAD] %s, %p\n", tmp->word, tmp->next);
            printf("[LOAD] %s, %p\n", tmp->next->word, tmp->next->next);
#endif
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
    bool isFreed = false;

    for (unsigned int i = 0; i < N; i++)
    {
        if (NULL != table[i])
        {
            isFreed = freeList(table[i]);

            if (false == isFreed)
            {
                return false;
            }
        }
    }

    return true;
}

bool freeList(node *n)
{
    if (NULL != n->next)
    {
        return freeList(n->next);
    }

    free(n);

    return true;
}