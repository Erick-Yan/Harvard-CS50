#include <stdio.h>
#include <cs50.h>



bool locked[4][4];

int candidate_count = 4;
int pair_count = 6;
int winner1[] = {1, 2, 3, 0, 2};
int loser1[] = {2, 3, 1, 3, 0};

int main(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    int score = 0;
    int ex = -1;

    int loser[candidate_count];
    int winner[candidate_count];
    for (int h = 0; h < candidate_count; h++)
    {
        loser[h] = -1;
        winner[h] = -1;
    }

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (loser1[i] != loser[j] && score == 0)
            {
                loser[i] = loser1[i];
                winner[i] = winner1[i];
                locked[winner1[i]][loser1[i]] = true;
                score++;
                break;
            }
            else if (loser1[i] == loser[j] && score > 0 && score < candidate_count - 1)
            {
                winner[i] = winner1[i];
                locked[winner1[i]][loser1[i]] = true;
                break;
            }
            else if (loser1[i] != loser[j] && score > 0 && score < candidate_count - 1 && j < candidate_count - 1 )
            {
                continue;
            }
            else if (loser1[i] != loser[candidate_count - 1] && score > 0 && score < candidate_count - 1)
            {
                loser[i] = loser1[i];
                winner[i] = winner1[i];
                locked[winner1[i]][loser1[i]] = true;
                score++;
                break;
            }
            else if (loser1[i] != loser[j] && score == candidate_count - 1)
            {
                continue;
            }
            else if (loser1[i] != loser[candidate_count - 1] && score == candidate_count - 1)
            {
                int a = 0;
                for (int l = 0; l < candidate_count; l++)
                {
                    if (winner[l] == loser1[i])
                    {
                        a++;
                    }
                }
                if (a > 0)
                {
                    ex = loser1[i];
                    score++;
                    break;
                }
                if (a == 0)
                {
                    loser[i] = loser1[i];
                    winner[i] = winner1[i];
                    break;
                }
            }
            else if (loser1[i] != ex && score > candidate_count - 1)
            {
                locked[winner1[i]][loser1[i]] = true;
                score++;
                break;
            }
        }
    }

    printf("Locked Array:\n");
    for (int k = 0; k < pair_count + 1; k++)
    {
        printf("%i\n", loser[k]);
    }
}