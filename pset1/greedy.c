/**
 *  pset1 - greedy.c
 *  Darren O'Connor
 *  @mellowdrifter
 *
 * Give lowest amount of coins for any change value entered
 */

#include <stdio.h>
#include <cs50.h>
#include <math.h>

// American focus, hence:
// quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢)

int amountLeft(int change, int coin)
{
    // What's left after giving a coin away ?
    int remain = change % coin;
    return remain;
}

int coinCount(int change, int coin)
{
    // How many coins?
    int count = change / coin;
    return count;
}

int centsConvert(float change)
{
    // Convert any value entered into cents
    int cents = round(change * 100);
    return cents;
}

int main(void)
{
    // Create list of coin values to iterate over later
    // Initialuse the change and coin count as well
    int coinValue[4] = {25, 10, 5, 1};
    float change;
    int count = 0;
    
    do
    {
        printf("O hai! How much change is owed? ");
        change = GetFloat();
    } while (change < 0.0);
    
    // I need cents values
    int cents = centsConvert(change);
    
    for(int i = 0; i < 4; i++)
    {
        int remaining = amountLeft(cents, coinValue[i]);
        count = count + coinCount(cents, coinValue[i]);
        cents = remaining;
        if (cents == 0)
        {
            break;
        }
    }
    printf("%i\n", count);
}
