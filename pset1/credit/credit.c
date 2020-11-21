#include <stdio.h>
#include <cs50.h>

#define DEBUG

long myPow(int nb, int exponent)
{
    if (exponent == 0) 
    {
        return 1;
    }
    else
    {
        return nb * myPow(nb, exponent - 1);
    }
}

int addDigits(int number)
{
    return number % 10 + number / 10;
}

int main(void)
{
    long cardNb = 0;
    
    do
    {
        cardNb = get_long("Credit card number: ");
    } 
    while (cardNb == LONG_MAX);
    
#ifdef DEBUG 
    printf("%ld\n", cardNb);
#endif
    
    int digits = 0;
    
    for (int i = 0; i < 18; i++)
    {
        if (cardNb / myPow(10, i) == 0)
        {
            digits = i;
            break;
        }
        
        if (i > 16)
        {
            printf("INVALID\n");
            return 0;
        }
    }
    
#ifdef DEBUG 
    printf("%d\n", digits);
#endif
    
    if (digits < 13)
    {
        printf("INVALID\n");
        return 0;
    }
    
#ifdef DEBUG 
    printf("%ld\n", cardNb / myPow(10, digits - 1));
#endif
    
    int accSum = 0;
    int digitsSum = 0;
    int sumNotMult = 0;
    int currentMult = 0;
    
    for (int i = 1; i <= digits; i = i + 2)
    {
        int currentDigit = 2 * ((cardNb / myPow(10, i)) % 10);
        accSum += currentDigit;
        digitsSum += addDigits(currentDigit);
        sumNotMult += (cardNb / myPow(10, i - 1)) % 10;
    }
    
    sumNotMult += digitsSum;
    
#ifdef DEBUG 
    printf("%d\n", sumNotMult);
#endif
    
    if (sumNotMult % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    
    else if ((cardNb / myPow(10, digits - 1)) == 4)
    {
        printf("VISA\n");
        return 0;
    }
    
    else if (digits == 15)
    {
        if ((cardNb / myPow(10, 13)) == 34 || (cardNb / myPow(10, 13) == 37))
        {
            printf("AMEX\n");
            return 0;
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }
    
    else if (digits == 16)
    {
        if ((cardNb / myPow(10, 14)) >= 51 && (cardNb / myPow(10, 14) <= 55))
        {
            printf("MASTERCARD\n");
            return 0;
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
}