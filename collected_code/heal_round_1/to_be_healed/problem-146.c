#include <stdio.h>

int findAsciiValueOfString(char *str) {
    int sum = 0;
    /* Possible weaknesses found:
     *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (int i = 0; str[i] != '\0'; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        sum += (int)str[i];
    }
    return sum;
}

int main() {
    char str[] = "Hello World!";
    int asciiSum = findAsciiValueOfString(str);
    printf("ASCII value of the characters in the string: %d\n", asciiSum);
    return 0;
}