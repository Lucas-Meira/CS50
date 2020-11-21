#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    // If there's more than 2 in line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    char *key = argv[1];

    int keyLength = strlen(key);


    if (keyLength != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }


    // Transform every letter in key to upper case
    for (int i = 0; i < keyLength; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must be alphanumeric.\n");
            return 1;
        }

        key[i] = (char) toupper(key[i]);

        for (int k = 0; k < i; k++)
        {
            if (key[i] == key[k])
            {
                printf("Character must be unique.\n");
                return 1;
            }
        }
    }

    // Get string from user
    char *plaintext = get_string("plaintext: ");
    // Allocate the same amount of memory for cipher text
    char *ciphertext = malloc(sizeof(plaintext));
    // Copy plaintext's content into ciphertext
    strcpy(ciphertext, plaintext);

    int textLength = strlen(plaintext);

    for (int i = 0; i < textLength; i++)
    {
        // Transform plaintext to upper case
        plaintext[i] = toupper(plaintext[i]);

        // Get index from 0 to 26
        int index = (int) plaintext[i] - 65;

        // Get corresponding char from key
        plaintext[i] = key[index];

        // Get cipher text
        if (isalpha(ciphertext[i]))
        {
            if (islower(ciphertext[i]))
            {
                ciphertext[i] = tolower(plaintext[i]);
            }
            else
            {
                ciphertext[i] = plaintext[i];
            }
        }

    }

    printf("ciphertext: %s\n", ciphertext);
    return 0;

}