#include <stdio.h>
#include <ctype.h>

void camelToSnake(char* str) {
    int i, j;
    char c;

    /* Possible weaknesses found:
     *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for(i = 0, j = 0; str[i] != '\0'; i++, j++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
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
    char str[100];

    printf("Enter a camel case string: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'str[0]' is initialized [premium-bughuntingUninit]
     */
    fgets(str, sizeof(str),stdin);

    camelToSnake(str);

    printf("The snake case string is: %s", str);

    return 0;
}