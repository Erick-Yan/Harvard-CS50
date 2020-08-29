#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long number = get_long("Number: ");

    int x = 0;
    if (number >= 1000000000000 && number < 10000000000000)
    {
        x = 13;
    }
    else if (number >= 100000000000000 && number < 1000000000000000)
    {
        x = 15;
    }
    else if (number >= 1000000000000000 && number < 10000000000000000)
    {
        x = 16;
    }

    //int div = (number/1000000000000);
    //printf("%i\n", div);

    int dub = 0;
    int innersum = 0;
    int sum1 = 0;
    long number1 = number * 0.1;
    long number2 = number;
    int sum2 = 0;

    while (number1)
    {
        dub = ((number1 % 10) * 2);
        while (dub)
        {
            innersum += dub % 10;
            dub /= 10;
        }
        sum1 = innersum;
        number1 /= 100;
    }

    while (number2)
    {
        sum2 += number2 % 10;
        number2 /= 100;
    }

    if ((sum1 + sum2) % 10 == 0 && x != 0)
    {
        if ((x == 13) && ((number / 1000000000000) == 4))
        {
            printf("VISA\n");
        }
        else if ((x == 15) && (((number / 10000000000000) == 34) || ((number / 10000000000000)  == 37)))
        {
            printf("AMEX\n");
        }
        else if ((x == 16) && (((number / 100000000000000) == 51) || ((number / 100000000000000) == 52) || ((number / 100000000000000) == 53) || ((number / 100000000000000) == 54) || ((number / 100000000000000) == 55)))
        {
            printf("MASTERCARD\n");
        }
        else if ((x == 16) && ((number / 1000000000000000) == 4))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}