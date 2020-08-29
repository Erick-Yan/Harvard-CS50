#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
//void merge(int left[], int right[], int mid[]);
//void mergesort(int win[]);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    bool yes = false;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            yes = true;
        }
    }
    return yes;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (i == j)
            {
                preferences[ranks[i]][ranks[j]] = 0;
            }
            else if (i < j)
            {
                preferences[ranks[i]][ranks[j]] += 1;
            }
        }
    }

    /*for (int t = 0; t < candidate_count; t++)
    {
        for (int y = 0; y < candidate_count; y++)
        {
            printf("%i\n", preferences[t][y]);
        }
    }*/
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int start = 0;
    for (int t = 0; t < candidate_count; t++)
    {
        for (int y = t; y < candidate_count; y++)
        {
            if (preferences[t][y] > preferences[y][t])
            {
                pairs[start].winner = t;
                pairs[start].loser = y;
                pair_count++;
                start++;
            }
            else if (preferences[t][y] == preferences[y][t])
            {
                pair_count += 0;
            }
            else if (preferences[t][y] < preferences[y][t])
            {
                pairs[start].winner = y;
                pairs[start].loser = t;
                pair_count++;
                start++;
            }
        }
    }
    //printf("%i\n", pair_count);
    /*printf("Winners:\n");
    for (int a = 0; a < pair_count; a++)
    {
        printf("%i\n", pairs[a].winner);
    }*/
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int new1[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        new1[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }

    /*printf("Diff:\n");
    for (int j = 0; j < pair_count; j++)
    {
        printf("%i\n", new1[j]);
    }*/

    for (int j = pair_count - 2; j >= 0; j--)
    {
        int value = new1[j];
        int hole = j;

        while (hole < pair_count - 1 && new1[hole + 1] > new1[hole])
        {
            new1[hole] = new1[hole + 1];
            hole++;
        }
        new1[hole] = value;
    }

    /*printf("Ordered:\n");
    for (int k = 0; k < pair_count; k++)
    {
        printf("%i\n", new1[k]);
    }*/

    int on = 0;
    pair pairs_copy[MAX * (MAX - 1) / 2];
    for (int l = 0; l < pair_count; l++)
    {
        for (int m = 0; m < pair_count; m++)
        {
            if (new1[l] == (preferences[pairs[m].winner][pairs[m].loser] - preferences[pairs[m].loser][pairs[m].winner]) && on < pair_count)
            {
                pairs_copy[on].winner = pairs[m].winner;
                pairs_copy[on].loser = pairs[m].loser;
                //printf("%i and %i - %i\n", on, m, pairs_copy[on].winner);
                on++;
            }
        }
    }

    //printf("Winners Sorted:\n");
    for (int n = 0; n < pair_count; n++)
    {
        pairs[n].winner = pairs_copy[n].winner;
        pairs[n].loser = pairs_copy[n].loser;
        //printf("%i\n", pairs[n].winner);
    }

}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
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
            if (pairs[i].loser != loser[j] && score == 0)
            {
                loser[i] = pairs[i].loser;
                winner[i] = pairs[i].winner;
                locked[pairs[i].winner][pairs[i].loser] = true;
                score++;
                break;
            }
            else if (pairs[i].loser == loser[j] && score > 0 && score < candidate_count - 1)
            {
                winner[i] = pairs[i].winner;
                locked[pairs[i].winner][pairs[i].loser] = true;
                break;
            }
            else if (pairs[i].loser != loser[j] && score > 0 && score < candidate_count - 1 && j < candidate_count - 1)
            {
                continue;
            }
            else if (pairs[i].loser != loser[candidate_count - 1] && score > 0 && score < candidate_count - 1)
            {
                loser[i] = pairs[i].loser;
                winner[i] = pairs[i].winner;
                locked[pairs[i].winner][pairs[i].loser] = true;
                score++;
                break;
            }
            else if (pairs[i].loser != loser[j] && score == candidate_count - 1)
            {
                continue;
            }
            else if (pairs[i].loser != loser[candidate_count - 1] && score == candidate_count - 1)
            {
                int a = 0;
                for (int l = 0; l < candidate_count; l++)
                {
                    if (winner[l] == pairs[i].loser)
                    {
                        a++;
                    }
                }
                if (a > 0)
                {
                    ex = pairs[i].loser;
                    loser[i] = pairs[i].loser;
                    winner[i] = pairs[i].winner;
                    score++;
                    break;
                }
                if (a == 0)
                {
                    loser[i] = pairs[i].loser;
                    winner[i] = pairs[i].winner;
                    break;
                }
            }
            else if (pairs[i].loser != ex && score > candidate_count - 1)
            {
                locked[pairs[i].winner][pairs[i].loser] = true;
                score++;
                break;
            }
        }
    }

    /*printf("Locked Array:\n");
    for (int k = 0; k < pair_count; k++)
    {
        for (int l = 0; l < pair_count; l++)
        {
            printf("%i\n", locked[k][l]);
        }
    }*/
}

// Print the winner of the election
void print_winner(void)
{
    //int winner = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        int sum = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                sum++;
            }
            else if (locked[candidate_count - 1][i] == false && sum == 0)
            {
                printf("%s\n", candidates[i]);
            }
        }
    }
}

