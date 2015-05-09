#include <stdio.h>
#include <cs50.h>

int sigma(int number) {
    if (number > 0) {
        return number + sigma(number - 1);
    }
    else {
        return number;
    }
}

int main(void) {
    printf("Please enter a number: ");
    int number = GetInt();
    
    printf("The sigma of %i is %i\n", number, sigma(number));
}
