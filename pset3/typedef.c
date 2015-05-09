#include <stdio.h>
#include <cs50.h>
#include <string.h>

#include "typedef.h"

#define CATS 2

int main(void) {
    cat cats[CATS];
    
    for (int i = 0; i < CATS; i++) {
    
        printf("Enter cat name: ");
        cats[i].name = GetString();
        
        printf("Enter cat age: ");
        cats[i].age = GetInt();
      
        printf("Enter cat colour: ");
        cats[i].colour = GetString();
    }
    
    for (int i = 0; i < CATS; i++) {
        printf("%s is %i years old and has a %s coat\n", cats[i].name, cats[i].age, cats[i].colour);
    }
}
