// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100;

// Hash table
node *table[N];

// For counting the amount of words in the dictionary
int wordCount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    
    for (node *cursor = table[index]; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
    }
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int value = 0;
    for (int i = 0; word[i] != '\0'; i++) // 'til the end of the word...
    {
        value += tolower(word[i]); // Doing math to get the table index
    }
    
    if (value > N-1)
    {
        return value % N; // If it be greater than the maximum index, return its module
    }
    return value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    
    char word[LENGTH + 1];
    int index;
    
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node)); // Allocating enough memory for the temp node
        if (n == NULL)
        {
            return false;
        }
        
        strcpy(n->word, word); // Putting the word in the node
        
        index = hash(word); // Defining where it's gonna be put in the table
        
        n->next = table[index]; // Putting in the table
        table[index] = n;
        
        wordCount++; // Increasing the words counter
    }
    
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *nxtNode = table[i]->next;
            free(table[i]);
            table[i] = nxtNode;
        }
    }
    return true;
}
