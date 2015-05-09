/**
 *  pset1 - mario
 *  Darren O'Connor
 *  @mellowdrifter
 *
 * Print out has wall right aligned to value entered
 */
 
#include <stdio.h>
#include <cs50.h>

int n;

void printSpace(int space)
{
    // Function to print out the spaces
    for (int i = 0; i <= space; i++) 
    {
        printf(" ");
    }
}

void printHash(int hash)
{
    // Function to print out the hashes
    for (int i = 0; i <= hash; i++) 
    {
        printf("#");
    }
    printf("\n");
}
    
int main(void)
{
    
    // Ask user for height of blocks. Max height is 23
    do 
    {
        printf("height: ");
        n = GetInt();
    } while (n < 0 || n > 23);
        
    for (int i = 0, j = n - 1; i < n; i++, j--) 
    {
        printSpace(j - 1);
        printHash(i + 1);
    }
}
