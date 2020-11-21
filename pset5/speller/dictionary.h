// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


// Prototypes
char toLower(char c);
bool freeList(node *n);
bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

#endif // DICTIONARY_H
