/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Linked list node
typedef struct node {
    char word[LENGTH];
    struct node* next;
}node;

node* hash_table[HASHTABLE_SIZE] = {NULL};

unsigned int word_count = 0;

/* unsigned int hash(const char* new_word)
{
    // DJB Hash - Modified
    unsigned int hash = 5381;
    const char* word = new_word;

    for(; *word; word++)
    {
        hash = ((hash << 5) + hash) + (*word);
    }
    return hash % HASHTABLE_SIZE;
} */

unsigned int hash(const char* new_word)
{
    // SDBM Hash - Modified
    unsigned int hash;
    const char* word = new_word;

    for(; *word; word++)
    {
        hash = *word + (hash << 6) + (hash << 16) - hash;
    }
    return hash % HASHTABLE_SIZE;
}


void insert(const unsigned int hash, const char* word)
{
    if (hash_table[hash] == NULL)
    {
        hash_table[hash] = (node*) malloc(sizeof(node));
        node* cur = hash_table[hash];
        strcpy(cur->word, word);
        cur->next = NULL;
    }
    else
    {
        // Traverse through linked list
        // Need to get to end of list in order to append
        node* cur = hash_table[hash];

        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = (node*) malloc(sizeof(node));
        cur = cur->next;
        strcpy(cur->word, word);
        cur->next = NULL;
    }   
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* initial_word)
{
    const char* word;
    word = initial_word; // apparently this is quicker
    // const unsigned int length = strlen(word);
    unsigned int length = 0;
    
    // won't be bigger than LENGTH...
    char low_word[LENGTH + 1];
    
    //for(unsigned int i = 0; i <= length; i++)
    //{
    //    low_word[i] = tolower(word[i]);
    //}
    
    for ( ; *initial_word; initial_word++,  length++)
    {
        low_word[length] = tolower(initial_word[length]);
    }
    low_word[length - 1] = '\0';
    
    const unsigned int hashed = hash(low_word);
    
    if (hash_table[hashed] != NULL)
    {
        node* cur = hash_table[hashed];
        if (strcmp(cur->word, low_word) == 0)
        {
            return true;
        }
        else
        {
            while(cur->next != NULL)
            {
                cur = cur->next;
                if (strcmp(cur->word, low_word) == 0)
                {
                    return true;
                }       
            }
        }
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{    
    // Create dictionary
    FILE* fp = fopen(dictionary, "r");
    
    if (fp == NULL)
    {
        return false;
    }
    
    char* word = malloc(sizeof(char[LENGTH]));
    while(fgets (word, LENGTH, fp) != NULL) 
    {
        word_count++;
        unsigned int length = strlen(word);
        for(unsigned int i = 0; i <= length; i++)
        {
            word[i] = tolower(word[i]);
        }

        word[length - 1]='\0';
        insert(hash(word), word);
    }
    free(word);
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return word_count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (unsigned int i = 0; i < HASHTABLE_SIZE; i++)
    {
        if (hash_table[i] != NULL)
        {
            node* cur = hash_table[i];
            while (cur != NULL) 
            {
                node* temp = cur;
                cur = cur->next;
                free (temp);
            }
        }
    }
    return true;
} 
