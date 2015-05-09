/**
 *  array mutate
 *  Darren O'Connor
 *  @mellowdrifter
 *
 * Change array details
 */
 
#include <stdio.h>


void square(int list[]) {
    for(int i = 0; i <3; i++) {
        list[i] *= list[i];
    }
}

int main(void) {
    int list[] = {2, 3, 4};
    
    square(list);
    
    for(int i = 0; i < 3; i++) {
        printf("%i\n", list[i]);
    }
    
}
