#include <stdio.h>
#include <string.h>
#include <cs50.h>

int main(void)
{
    string text = get_string("Text: ");

    unsigned int nbLetters = 0;
    unsigned int nbWords = 0;
    unsigned int nbSentences = 0;

    int n = strlen(text);

    for (int i = 0; i <= n; i++)
    {
        if (text[i] == ' ' || text[i] == '\0')
        {
            nbWords++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            nbSentences++;
        }
        else if (text[i] >= 'A' && text[i] <= 'z')
        {
            nbLetters++;
        }
    }


    //printf("Number of letters: %d\nNumber of words: %d\nNumber of sentences: %d\n", nbLetters, nbWords, nbSentences);

    float L = 100 * (float) nbLetters / nbWords;
    float S = 100 * (float) nbSentences / nbWords;

    float index = 0.0588 * L - 0.296 * S - 15.8;

    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if ((index - (int) index) >= 0.5)
    {
        printf("Grade %d\n", (int) index + 1);
    }
    else
    {
        printf("Grade %d\n", (int) index);
    }

    return 0;
}