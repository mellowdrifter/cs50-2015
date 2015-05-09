/**
 *  pset2 - initials.c
 *  Darren O'Connor
 *  @mellowdrifter
 *
 * Print out the initials of any name entered
 */
 
#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    char* name = GetString();
    
    int j = strlen(name);
    
    for(int i = 0; i < j; i++)
    // Lets iterate over each letter
    {
        if (i == 0)
        // First letter will always be a capital
        {
            if ((int) name[i] > 96 && (int) name[i] < 123)
            // Handle lower and uppercase letters differently
            {
                printf("%c", name[i] - 32);
            }
            else
            {
                printf("%c", name[i]);
            }
        }
        
        // Check if previous letter was space. 
        // Can then assume letter is first of next name
        else if(name[i - 1] == ' ')
        {
            if ((int) name[i] > 96 && (int) name[i] < 123)
            {
                printf("%c", name[i] - 32);
            }
            else
            {
                printf("%c", name[i]);
            }
        }
    }
    printf("\n");
}
