/**
 *  pset2 - vigenere.c
 *  Darren O'Connor
 *  @mellowdrifter
 *
 * Creates a vigenere version of string entered
 */
 
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char encrypt(char letter, int key, string cipher)
{
    /* Does all the required cipher work. Need to check
       if both original text and cipher is upper or lower
       as each has a different starting ascii value */

    int remove;
    
    if (isupper(cipher[key]))
    {
        remove = 65;
    }
    else
    {
        remove = 97;
    }
    if (isupper(letter))
    {
        letter = (((letter - 65) + (cipher[key] - remove)) % 26) + 65;
    }
    else
    {
        letter = (((letter - 97) + (cipher[key] - remove)) % 26) + 97;
    }
    return letter;
}
 
int main(int argc, string argv[])
{

    // Only one argument allowed
    if (argc != 2)
    {
        printf("Usage: ./caeser <key>\n");
        return 1;
    }
    
    // Argument can only contain letters
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Usage: ./caeser <key>\n");
            return 1;
        }
    }
    
    // Get some text to work on
    string message = GetString();
    
    // Size of key needed to ensure cipher wraps later
    int key_size = strlen(argv[1]);
    int n = strlen(message);
    
    // Go through each letter and encrypt if alpha
    // Use modulo to keep iterating over short key
    for (int i = 0, k = 0; i < n; i++)
    {
        if (isalpha(message[i]))
        {
            printf("%c", encrypt(message[i], k % key_size, argv[1]));
            k++;
        }
        else
        {
            printf("%c", message[i]);
        }
    }
    
    printf("\n");
    
    return 0;
}
