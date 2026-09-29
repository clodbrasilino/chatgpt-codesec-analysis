#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'calloc'
  */

#define NO_OF_CHARS 256

char firstRepeating(char *str) {
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'calloc'
     *  incompatible implicit declaration of built-in function 'calloc' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'calloc' [-Wimplicit-function-declaration]
     */
    int *count = (int *)calloc(sizeof(int), NO_OF_CHARS);
    int i;
    for (i = 0; *(str+i); i++)
        count[*(str+i)]++;
    for (i = 0; *(str+i); i++)
        if (count[*(str+i)] > 1)
            /* Possible weaknesses found:
             *  leak of 'count' [CWE-401] [-Wanalyzer-malloc-leak]
             */
            return str[i];

    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     */
    free(count);
    return '\0';
}

int main() {
    char str[] = "heleworld";
    printf("%c", firstRepeating(str));
    return 0;
}