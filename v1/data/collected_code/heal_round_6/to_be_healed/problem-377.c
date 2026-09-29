#include<stdio.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strcspn'
  */

#define MAX_SIZE 100

void removeChar(char* str, char c) {
    if(str == NULL)
        return;

    int count = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] != c) {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_SIZE];
    char c; 

    printf("Enter a string: ");
    if(fgets(str, MAX_SIZE, stdin))
        /* Possible weaknesses found:
         *  include '<string.h>' or provide a declaration of 'strcspn'
         *  implicit declaration of function 'strcspn' [-Wimplicit-function-declaration]
         *  incompatible implicit declaration of built-in function 'strcspn' [-Wbuiltin-declaration-mismatch]
         */
        str[strcspn(str, "\n")] = 0;

    printf("Enter the character to remove: ");
    if(scanf(" %c", &c))
        removeChar(str, c);

    printf("String after removing character '%c': %s\n", c, str);

    return 0;
}