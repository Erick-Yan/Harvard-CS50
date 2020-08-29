#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    bool yes = false;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            yes = true;
        }
    }
    return yes;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int star = 0;
    if (candidate_count > 1)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            for (int j = i + 1; j < candidate_count; j++)
            {
                if (candidates[i].votes > candidates[j].votes && candidates[i].votes > star)
                {
                    star = candidates[i].votes;
                }
                else if (candidates[i].votes < candidates[j].votes && candidates[j].votes > star)
                {
                    star = candidates[j].votes;
                    break;
                }
                else if (candidates[i].votes == candidates[j].votes && star < candidates[j].votes)
                {
                    star = candidates[i].votes;
                    break;
                }
            }
        }

        //printf("%i\n", star);

        string lar[candidate_count];
        int begin = 0;
        for (int k = 0; k < candidate_count; k++)
        {
            if (candidates[k].votes == star)
            {
                lar[begin] = candidates[k].name;
                begin++;
            }
        }

        for (int l = 0; l < begin; l++)
        {
            printf("%s\n", lar[l]);
        }
    }
    else
    {
        printf("%s\n", candidates[0].name);
    }

}

