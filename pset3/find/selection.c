/**
 *  pset3 - selection.c
 *  Darren O'Connor
 *  @mellowdrifter
 *
 * Selection search test
 */
 #include <stdio.h>

int list[] = {6, 5, 9, 2, 1, 4, 3};

void goSort(int list[], int size) {

    int temp;
    int changed = 0;
    int index = 0;
    int min;
    
    do {
        for (int i = 0; i < size; i++) {
            printf("%i\t", list[i]);
        }
        printf("\n");
        
        min = list[index];
        
        for (int i = index; i < size; i++) {
            if (list[i] < min) {
                min = list[i];
            }
        temp = min;
        
            
    
    
    
    

int main(void) {
    goSort(list, 7);
    
    for(int i = 0; i < 7; i++) {
        printf("%i\t", list[i]);
    }
    printf("\n");
}
