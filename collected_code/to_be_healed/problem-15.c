#include <stdio.h>

void splitString(char *str) {
    int i;
    /* Possible weaknesses found:
     *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (i = 0; str[i] != '\0'; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (str[i] >= 'a' && str[i] <= 'z') {
            printf("\n");
        } else {
            /* Possible weaknesses found:
             *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            printf("%c", str[i]);
        }
    }
}

int main() {
    char str[] = "SplitThisString";
    splitString(str);
    return 0;
}