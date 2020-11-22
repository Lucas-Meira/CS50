// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


#define DJB

// Number of buckets in hash table
const unsigned int N = 0xFFFF;

// Hash table
node *table[N];
node *last[N];

unsigned int hashes = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int hashValue = 0;
    char lowerWord[LENGTH + 1];
    int index = 0;

    strcpy(lowerWord, word);

    while (lowerWord[index] != '\0')
    {
        lowerWord[index] = tolower(lowerWord[index]);

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
#ifdef DJB
    unsigned long hashValue = 5381;
    int c = *word;

    while (c != 0)
    {
        hashValue = ((hashValue << 5) + hashValue) + c; /* hash * 33 + c */
        c = *++word;
    }

#endif
#ifdef CRC
    uint16_t hashValue = 0xFFFF;

    for (int pos = 0, len = strlen(word); pos < len; pos++)
    {
        hashValue ^= (uint16_t) word[pos];

        for (int i = 8; i != 0; i--)
        {
            if ((hashValue & 0x0001) != 0)
            {
                hashValue >>= 1;
                hashValue ^= 0xA001;
            }
            else
            {
                hashValue >>= 1;
            }
        }
    }
#endif
    //hashValue = *word - 'a';
#ifdef DEBUG
    printf("[HASH] %d\n", hashValue);
#endif
    return hashValue & 0xFFFF;
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

    char word[LENGTH + 2];

    while (NULL != fgets(word, LENGTH + 2, file))
    {
        hashes++;

        // Remove \n
        word[strlen(word) - 1] = '\0';
        node *item = (node *) malloc(sizeof(node));

        unsigned int hashValue = hash(word);

        if (NULL == table[hashValue])
        {
            strcpy(item->word, word);
            item->next = NULL;

            table[hashValue] = item;

            last[hashValue] = table[hashValue];
#ifdef DEBUG
            printf("[LOAD] %s, %p\n", table[hashValue]->word, table[hashValue]->next);
#endif
        }
        else
        {
            strcpy(item->word, word);
            item->next = NULL;

            last[hashValue]->next = item;

            last[hashValue] = last[hashValue]->next;
#ifdef DEBUG
            printf("[LOAD] %s, %p\n", table[hashValue]->word, table[hashValue]->next);
#endif
        }
    }

    fclose(file);

    return true;
}

unsigned long freeCount = 0;
// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return hashes;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    bool isFreed = false;

    for (size_t i = 0; i < N; i++)
    {
        if (NULL != table[i])
        {
            node *tmp = table[i];
            node *ntmp = table[i]->next;
            if (NULL == tmp->next)
            {
                free(tmp);
                freeCount++;
            }
            else
            {
                while (1)
                {
                    free(tmp);
                    tmp = ntmp;
                    ntmp = ntmp->next;
                    freeCount++;

                    if(NULL == ntmp)
                    {
                        break;
                    }
                }

                free(tmp);
                freeCount++;
            }
        }
    }

    return true;
}