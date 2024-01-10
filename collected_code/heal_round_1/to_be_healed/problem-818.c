#include <stdio.h>

int countLowerCase(char* str) {
    int count = 0;
    int i = 0;

    /* Possible weaknesses found:
     *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    while (str[i] != '\0') {
        /* Possible weaknesses found:
         *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (str[i] >= 'a' && str[i] <= 'z') {
            count++;
        }
        i++;
    }

    return count;
}

int main() {
    char* text = "Hello, World!";
    int result = countLowerCase(text);

    printf("Number of lower case letters: %d\n", result);

    return 0;
}