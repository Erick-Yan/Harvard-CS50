#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int size;
    do
    {
        size = get_int("Height: ");
    }
    while (size < 1 || size > 8);

    for (int row = 1; row <= size; row++)
    {
        for (int space = size - row; space >= 1; space--)
        {
            printf(" ");
        }

        for (int column = 0; column < row; column++)
        {
            printf("#");
        }

        printf("  ");

        for (int column = 0; column < row; column++)
        {
            printf("#");
        }

        printf("\n");
    }
}