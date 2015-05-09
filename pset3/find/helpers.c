/**
 *  pset3 - helper.c
 *  Darren O'Connor
 *  @mellowdrifter
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */

bool binSearch(int value, int values[], int min, int max)
{

    int middle = (min + max) / 2;
    // Binary Search
    if (max < min)
    {
        return false;
    }
    else
    {
        if (value < values[middle])
        {
            return binSearch(value, values, min, middle - 1);
        }
        else if (value > values[middle])
        {
            return binSearch(value, values, middle + 1, max);
        }
        else
        {
            return true;
        }
    }  
}

bool search(int value, int values[], int n)
{   
    return binSearch(value, values, 0, n);
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Bubble sort. Come back and do a selection sort later?
    int temp;
    int changed = 0;
    
    do
    {
        for (int i = 1; i < n; i++)
        {
            if (values[i] < values[i - 1])
            {
                temp = values[i];
                values[i] = values[i - 1];
                values[i - 1] = temp;
                changed = 1;
                break;
            }
            else
            {
                changed = 0;
            }
        } 
    } 
    while (changed == 1);
}
