#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    bool start = false;
    if (start == false)
    {
        if (argc != 2)
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
        else
        {
            for (int s = 0; s < strlen(argv[1]); s++)
            {
                for (int e = s + 1; e <= strlen(argv[1]); e++)
                {
                    if (isalpha(argv[1][s]) == 0)
                    {
                        printf("Only letters!\n");
                        return 1;
                    }
                    else if (argv[1][e] == argv[1][s])
                    {
                        printf("No repeating letters!\n");
                        return 1;
                    }
                }
                start = true;
            }
        }
    }

    if (start == true && strlen(argv[1]) == 26)
    {
        string text = get_string("plaintext:  ");
        string alph = "abcdefghijklmnopqrstuvwxyz";
        char pos[strlen(text)];
        for (int i = 0; i <= strlen(text); i++)
        {
            if (isupper(text[i]) != 0)
            {
                char a = tolower(text[i]);
                for (int y = 0; y < 26; y++)
                {
                    if (alph[y] == a)
                    {
                        pos[i] = toupper(argv[1][y]);
                    }
                }
            }
            else if (islower(text[i]) != 0)
            {
                char a = tolower(text[i]);
                for (int y = 0; y < 26; y++)
                {
                    if (alph[y] == a)
                    {
                        pos[i] = tolower(argv[1][y]);
                    }
                }
            }
            else
            {
                pos[i] = text[i];
            }

        }
        printf("ciphertext: %s\n", pos);
        return 0;
    }
    else if (start == true && strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
}