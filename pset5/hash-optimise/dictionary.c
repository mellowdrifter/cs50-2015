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

// Bigger table means more to initilise and free
// But less collissions...
node* hash_table[HASHTABLE_SIZE] = {NULL};

unsigned int word_count = 0;

/**
 * Hash function
 */
/*unsigned int hash(const char* word)
{
    // No need to reinvent the wheel. Use hash function 
    // from http://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/
    // Tweaked just a little bit
    const int length = strlen(word);
    unsigned int hash = 0;
    for (int i = 0; i < length; i++)
        hash = (hash << 2) ^ word[i];
        
    //printf("You sent the word %s, the size is %i and the hash is %i\n", word, length, hash % HASHTABLE_SIZE); 
    return hash % HASHTABLE_SIZE;
} */

unsigned int hash(char* word)
{
    unsigned int hash;
    char* new_word;
    new_word = word; // apparently this is quicker
    for(; *new_word; new_word++)
        hash = (hash << 2) ^ *new_word;
        
    return hash % HASHTABLE_SIZE;
}

/* unsigned int hash(char *word)
{
	unsigned int h = 0;
	for(; *word; word++)
		h = MULT * h + *word;
	return h % HASHTABLE_SIZE;
} */

void insert(const unsigned int hash, char* word)
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
bool check(const char* word)
{
    unsigned int length = strlen(word);
    char low_word[length + 1];
    for(unsigned int i = 0; i <= length; i++)
    {
        low_word[i] = tolower(word[i]);
    }
    unsigned int hashed = hash(low_word);
    
    if (hash_table[hashed] == NULL)
    {
        return false;
    }
    else
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
        // Have to remove the newline otherwise hash doesn't match up later
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
