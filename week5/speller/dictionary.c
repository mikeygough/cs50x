// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N]; // hash table is an array of N node pointers

// Counter variable
int glob_counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // first, hash word to obtain a has value
    unsigned int index = hash(word);

    // set the cursor
    node *tmp = table[index];

    // loop through linked list
    while (tmp != NULL)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory (hash table), returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open dictionary file
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        printf("Could not open %s\n", dictionary);
        return 1;
    }

    // read strings from file one at a time
    char words[LENGTH + 1]; // initial array of 45 + 1 characters to store the word
    while (fscanf(f, "%s", words) != EOF)
    {
        // create a new node for each word
        node *n = malloc(sizeof(node)); // store the address of this node inside of n
        if (n == NULL) // malloc memory check
        {
            return 1;
        }

        // put data inside the node using strcpy
        strcpy(n->word, words);

        // set the next pointer to NULL (if you don't know what the next pointer is)
        n->next = NULL;

        // hash word to obtain a hash value
        unsigned int index = hash(n->word);

        // insert node into hash table at that location
        n->next = table[index];
        table[index] = n;

        glob_counter += 1;
    }
    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (glob_counter > 0)
    {
        return glob_counter;
    }
    return 0;

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // iterate through array
    for (int i = 0; i < N; i++)
    {
        // set cursor
        node *cursor = table[i];
        // free
        while (cursor != NULL)
        {
            // create tmp
            node *tmp = cursor;
            // move cursor to next node, temp stores previous
            cursor = cursor->next;
            // free tmp
            free(tmp);
        }
        if (cursor == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}

