/**
 *  pset2 - caesar.c
 *  Darren O'Connor
 *  @mellowdrifter
 *
 * Basic cypher
 */
 
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// ci = (pi + k) % 26

int main(int argc, string argv[])
{

    // Only one argument allowed
    if (argc != 2)
    {
        printf("Usage: ./caeser <key>\n");
        return 1;
    }
    
    // convert ascii key value to integer
    int key = atoi(argv[1]);
    
    // Key will be zero if a number not entered
    if (key == 0)
    {
        return 1;
    }
    
    string message = GetString();
    
    for (int i = 0, n = strlen(message); i < n; i++)
    {
        
        // We only change alpha characters
        if (isalpha(message[i]))
        {
        
            // Upercase handled slightly differently
            if (isupper(message[i]))
            {
                printf("%c", (((message[i] - 64) + key) % 26) + 64);
            } 
            else
            {
                printf("%c", (((message[i] - 97) + key) % 26) + 97);
            }
        }
        else
        {
            printf("%c", message[i]);
        }
    }
    printf("\n");
}
