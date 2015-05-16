/**
 *  pset5 - dictionary.c
 *  Darren O'Connor
 *  @mellowdrifter
 *
 * Trie version of dictionary.c
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Struct for trie
typedef struct node {

    // bool specifies end of word
    bool is_end;
    
    // Pointer to 26 letters and apostrophe
    struct node* child[ALPHABET];
}node;

// Root of data strcture. Have to assign it here
// so other functions have access to it
node* root;

int word_count = 0;
    
void clean(node* current) {

    // When a new node is spawned, we need to ensure all values
    // are set to NULL
    for (int i = 0; i < ALPHABET - 1; i++) {
        current->child[i] = NULL;
    }
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int length = strlen(word);
    
    node* current = root;
    int letter;
    // Go through each letter. If at anytime we don't see a letter
    // in the trie, return false.
    // If we get to the end, return the end of word value
    // which is already 'true'
    for (int i = 0; i < length; i++) 
    {
        if ((int) word[i] == 39)
        {
            letter = 26;
        }
        else if (isupper(word[i]))
        {
            letter = (int) word[i] - 'A';
        }
        else if (islower(word[i]))
        {
            letter = (int) word[i] - 'a';
        }
        if (current->child[letter] == NULL) {
            return false;
        }
        current = current->child[letter];
    }
    return current->is_end;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // Currently a trie.
    
    // Create dictionary
    FILE* fp = fopen(dictionary, "r");
    
    if (fp == NULL)
    {
        return false;
    }
    
    // Create initial node. No end of word
    root = (node*) malloc(sizeof(node));
    root->is_end = false;
    
    // Initialise cursor that we will mode around
    
    int length;
    int letter;
    
    // Ensure all values set to NULL
    clean(root);
    
    // Read words and insert into trie. Free up RAM when done
    char* word = malloc(sizeof(char[LENGTH]));
    while(fgets (word, LENGTH, fp)!=NULL) 
    {
        node* current = root;
        // Count words added
        word_count++;
        length = strlen(word);
        
        // Go over each letter in the word
        for (int i = 0; i < length - 1; i++) 
        {       
            if ((int) word[i] == 39)
            {
                letter = 26;
            }
            else if (isupper(word[i]))
            {
                letter = (int) word[i] - 'A';
            }
            else if (islower(word[i]))
            {
                letter = (int) word[i] - 'a';
            }
            // If pointing to NULL value, spawn a new node
            // ensure new spawn has NULL values
            if (current->child[letter] == NULL) 
            {
                current->child[letter] = (node*) malloc(sizeof(node));
                //node* temp = current->child[letter];
                //clean(temp);
            }
            
            // Move to next node
            current = current->child[letter];
        }
        // Once we get to the end, ensure that we insert a true value here
        current->is_end = true;
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

int killTrie(node* current) {

    // Recursively go into each node and
    // check if any children are not NULL
    // Will eventually kill all nodes
    for (int i = 0; i < ALPHABET; i++) 
    {
        if (current->child[i] != NULL) 
        {
            killTrie(current->child[i]);
        }
    }
    free(current);
    return 1;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    node* current = root;
    killTrie(current);
    return true;   
}
