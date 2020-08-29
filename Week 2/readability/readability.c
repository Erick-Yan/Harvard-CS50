#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

float count_letters(string x);
float count_words(string y);
float count_sent(string z);

int main(void)
{
    string text = get_string("Text: ");
    float L = count_letters(text) * 100 / count_words(text);
    float S = count_sent(text) * 100 / count_words(text);
    int index = round(((0.0588 * L) - (0.296 * S)) - 15.8);

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %.0f\n", round(index));
    }
}

float count_letters(string x)
{
    float letter = 0;
    for (int i = 0; i < strlen(x); i++)
    {
        if (isdigit(x[i]) == 0 && ispunct(x[i]) == 0 && isspace(x[i]) == 0)
        {
            letter += 1;
        }
    }

    return letter;
}

float count_words(string y)
{
    float word = 0;
    for (int i = 0; i < strlen(y); i++)
    {
        char a = y[i];
        if ((isspace(a) != 0))
        {
            word += 1;
        }
    }

    word = word + 1;

    return word;
}

float count_sent(string z)
{
    float sent = 0;
    for (int i = 0; i < strlen(z); i++)
    {
        if (z[i] == '.' || z[i] == '!' || z[i] == '?')
        {
            sent += 1;
        }
    }

    return sent;
}