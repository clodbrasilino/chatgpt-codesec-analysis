#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'calloc'
  */

#define NO_OF_CHARS 256

char firstRepeatingChar(char* str) {
    /* Possible weaknesses found:
     *  implicit declaration of function 'calloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'calloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'calloc'
     */
    int* count = (int*)calloc(sizeof(int), NO_OF_CHARS);
    for (int i = 0; *(str + i); i++)
        count[*(str + i)]++;

    for (int i = 0; *(str + i); i++)
        if (count[*(str + i)] > 1) {
            /* Possible weaknesses found:
             *  include '<stdlib.h>' or provide a declaration of 'free'
             *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
             *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
             */
            free(count);
            return *(str + i);
        }

    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     */
    free(count);
    
    return '\0';
}

int main() {
    char str[] = "programming";
    char result = firstRepeatingChar(str);
    if (result != '\0') {
        printf("The first repeating character is %c", result);
    } else {
        printf("No repeating character found");
    }
    
    return 0;
}