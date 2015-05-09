/**
 *  pset3 - bubble.c
 *  Darren O'Connor
 *  @mellowdrifter
 *
 * Bubble search test
 */
 
#include <stdio.h>

int list[] = {6, 5, 9, 2, 1, 4, 3};

void goSort(int list[], int size) {

    int temp;
    int changed = 0;
    
    do {
        for (int i = 0; i < size; i++) {
            printf("%i\t", list[i]);
        }
        printf("\n");
        for (int i = 1; i < size; i++) {
            if (list[i] < list[i - 1]) {
                temp = list[i];
                list[i] = list[i - 1];
                list[i - 1] = temp;
                changed = 1;
                break;
            }
            else {
                changed = 0;
            }
        } 
    } while (changed == 1);
}
        
             
    
int main(void) {
    goSort(list, 7);
    
    for(int i = 0; i < 7; i++) {
        printf("%i\t", list[i]);
    }
    printf("\n");
}
