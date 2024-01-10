#include <stdio.h>

int countNumericValues(char *str) {
    int count = 0;
    /* Possible weaknesses found:
     *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (int i = 0; str[i] != '\0'; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (str[i] >= '0' && str[i] <= '9') {
            count++;
        }
    }
    return count;
}

int main() {
    char str[] = "Hello123World456";
    int numericCount = countNumericValues(str);
    printf("Number of numeric values in the string: %d\n", numericCount);
    return 0;
}