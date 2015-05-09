/**
 *  Binary Search - FIX!!!!!
 *  Darren O'Connor
 *  @mellowdrifter
 *
 * Cracks some codes. STILL NEEDS WORK!!!
 */
 
#include <stdio.h>
#include <cs50.h>

int list[] = {1, 5, 78, 144, 237, 333, 450, 900, 1500};

int findMidpoint(int min, int max) {
    return min + max / 2;
}

int binSearch(int key, int list[], int min, int max) {
    if (max < min) {
        return -1;
    }
    else {
        int midpoint = findMidpoint(min, max);
        if (key < list[midpoint]) {
            binSearch(key, list, min, midpoint - 1);
        }
        else if (key > list[midpoint]) {
            binSearch(key, list, midpoint + 1, max);
        }
        return midpoint;
    }
}      
        
int main(void) {
    printf("Enter a number from 1 to 1500 and I will see if I have it in my list");
    printf("\nIf it is, I'll tell you where in my list it is. ");
    
    int getnum;
    
    do {
        getnum = GetInt();
    } while (getnum > 1500 || getnum < 1);
    
    int index = binSearch(getnum, list, 1, 1500);
    
    if (index) {
        printf("You number is located in position %i\n", index);
    }
    else {
        printf("Your number is not in the list\n");
   }
}
    
