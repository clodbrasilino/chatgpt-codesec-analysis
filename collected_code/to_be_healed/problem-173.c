#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'isalnum'
  */

void removeNonAlphanumeric(char* str) {
    if (str == NULL) {
        return;
    }
    int i, j;
    for (i = 0, j = 0; str[i] != '\0'; i++) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'isalnum' [-Wimplicit-function-declaration]
         */
        if (isalnum(str[i])) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[100];
    printf("Enter a string: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'str[0]' is initialized [premium-bughuntingUninit]
     */
    fgets(str, sizeof(str), stdin);
    removeNonAlphanumeric(str);
    printf("String after removing non-alphanumeric characters: %s", str);
    return 0;
}