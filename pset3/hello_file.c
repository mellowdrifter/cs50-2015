/**
 *  Writes data to multiple text files
 *  Darren O'Connor
 *  @mellowdrifter
 *
 * **********
 */
 
#include <stdio.h>

int main(void) {
    FILE* file = fopen("hello.txt", "w");
    FILE* file2 = fopen("hello2.txt", "w");
    if (file == NULL || file2 == NULL) {
        return 1;
    }
    
    fputs("Hello, world\n", file); // Unlike python, argument is filename
    fprintf(file2, "Hello, world, again!\n"); // Miss f.write with f as file handler :(
    
    fclose(file);
    fclose(file2);
}
