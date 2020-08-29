// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include <strings.h>

#include <string.h>

#include <ctype.h>

#include <stdlib.h>

#include <stdio.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 150000;

// Hash table
node *table[N];

int word_size = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char wordy[strlen(word) + 1];
    for (int i = 0; i < strlen(word); i++)
    {
        wordy[i] = tolower(word[i]);
    }

    wordy[strlen(word)] = '\0';

    int index_c = hash(wordy);

    for (node *tmp = table[index_c]; tmp != NULL; tmp = tmp->next)
    {
        if ((strcasecmp(wordy, tmp->word)) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char* word)
{
        unsigned int hash_value = 0;
        for (int i = 0, n = strlen(word); i < n; i++)
        {
             hash_value = (hash_value << 2) ^ word[i];
        }
        return hash_value % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *open = fopen(dictionary, "r");
    if (open == NULL)
    {
        return false;
    }

    char *word = malloc(LENGTH + 1);
    while (fscanf(open, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (word == NULL)
        {
            return false;
        }
        strcpy(n->word, word);

        int index = hash(word);

        n->next = table[index];
        table[index] = n;
        word_size++;
    }
    free(word);
    fclose(open);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    int chek = 0;
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp = table[i];
        while (tmp != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
        chek++;
    }

    if (chek == N)
    {
        return true;
    }
    else
    {
        return false;
    }
}
