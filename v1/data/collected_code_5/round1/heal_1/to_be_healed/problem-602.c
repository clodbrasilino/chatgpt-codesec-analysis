#include <stdio.h>
#include <string.h>

#define NO_OF_CHARS 256

char firstRepeating(char *str) {
    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'calloc'
     *  call to undeclared library function 'calloc' with type 'void *(unsigned long, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    int *count = (int *)calloc(sizeof(int), NO_OF_CHARS);
    int i;
    for (i = 0; *(str+i); i++)
        count[*(str+i)]++;
    for (i = 0; *(str+i); i++)
        if (count[*(str+i)] > 1)
            return str[i];

    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    free(count);
    return '\0';
}

int main() {
    char str[] = "heleworld";
    printf("%c", firstRepeating(str));
    return 0;
}