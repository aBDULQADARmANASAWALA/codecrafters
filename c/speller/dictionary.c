// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
// You will likely want to increase this depending
// on your own implementation of hash.
const unsigned int N = 45;

// Hash table
node *table[N];
node *ptr;
int word_count = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // set all table pointers to null
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        fclose(source);
        return false;
    }

    char string[LENGTH + 1];

    // add each word to the hash table
    while (fscanf(source, "%s", string) != EOF)
    {
        // create space for new hash table node
        ptr = malloc(sizeof(node));
        if (ptr == NULL)
        {
            return false;
        }
        ptr->next = NULL;

        // copy word into new node
        strcpy(ptr->word, string);

        // hash the word to obtain its hash value
        unsigned int hash_val = hash(ptr->word);

        // insert the new node into hash table
        if (table[hash_val] == NULL)
        {
            table[hash_val] = ptr;
        }
        else
        {
            ptr->next = table[hash_val];
            table[hash_val] = ptr;
        }

        // for size function
        word_count++;
    }

    // load completed successfully, close file
    fclose(source);
    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // dont forget to change "N" above
    return (unsigned int) strlen(word);
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
    return 0;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // get the hash value
    int hash_val = hash(word);

    // search through the hash table
    if (table[hash_val] != NULL)
    {
        ptr = table[hash_val];
    }
    else
    {
        return false;
    }

    while (true)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
        else
        {
            // cannot use ternary operator with break
            if (ptr->next == NULL)
            {
                break;
            }
            else
            {
                ptr = ptr->next;
            }
        }
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *c, *n;
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            c = table[i];
            n = c->next;
            while (true)
            {
                if (n == NULL)
                {
                    free(c);
                    break;
                }
                free(c);
                c = n;
                n = c->next;
            }
        }
    }
    return true;
}
