#include <stdio.h>

void findSequences(char* str) {
    int i = 0;
    /* Possible weaknesses found:
     *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    while (str[i] != '\0') {
        /* Possible weaknesses found:
         *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (str[i] >= 'A' && str[i] <= 'Z') {
            /* Possible weaknesses found:
             *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            putchar(str[i]);
            i++;
            /* Possible weaknesses found:
             *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            while (str[i] >= 'a' && str[i] <= 'z') {
                /* Possible weaknesses found:
                 *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                putchar(str[i]);
                i++;
            }
            putchar('\n');
        }
        else {
            i++;
        }
    }
}

int main() {
    char str[] = "ABcD efGhIjKlM";
    findSequences(str);
    return 0;
}