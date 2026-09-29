#include <stdio.h>

// Function to convert string to lower case
void toLowerCase(char *str) {
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
            str[i] = str[i] + 32;
        }
        i++;
    }
}

int main() {
    char str[] = "Hello World";
    printf("Before Conversion: %s\n", str);
    toLowerCase(str);
    printf("After Conversion: %s\n", str);

    return 0;
}