/**
 *  Pointer test
 *  Darren O'Connor
 *  @mellowdrifter
 *
 * ***
 */

#include <stdio.h>
#include <cs50.h>

// Use a pointer, without a regular variable.
// Allocate some RAM, put a value into it
// then read it directly

int main(void) {
    int* ptr = malloc(sizeof(int));
    if (ptr == NULL) {
        return 1;
    }
    
    *ptr = GetInt();
    
    printf("Your number is %i\n", *ptr);
    
    free(ptr); // Free what malloc gave me above.
}
