#include <stdio.h>
#include <ctype.h>
/* Possible weaknesses found:
 *  include '<string.h>' or provide a declaration of 'strlen'
 */
#define MAX_LENGTH 101

void camelToSnake(char* str) {
    int i, j;
    char c;

    for(i = 0, j = 0; str[i] != '\0'; i++, j++) {
        c = str[i];

        if(isupper(c)) {
            str[j] = '_';
            str[++j] = tolower(c);
        } else {
            str[j] = c;
        }
    }
    str[j] = '\0';
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_LENGTH];

    printf("Enter a camel case string: ");
    fgets(str, sizeof(str), stdin);
    
    /* Possible weaknesses found:
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     *  include '<string.h>' or provide a declaration of 'strlen'
     *  incompatible implicit declaration of built-in function 'strlen' [-Wbuiltin-declaration-mismatch]
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    if (str[strlen(str)-1] == '\n')
      /* Possible weaknesses found:
       *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
       */
      str[strlen(str)-1] = '\0';

    camelToSnake(str);

    printf("The snake case string is: %s\n", str);

    return 0;
}