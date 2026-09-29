#include <stdio.h>

int countRotationsOfOddValueBinaryString(char *str) {
    int count = 0;
    int i = 0;
    /* Possible weaknesses found:
     *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    while (str[i] != '\0') {
        /* Possible weaknesses found:
         *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        int num = str[i] - '0';
        if (num % 2 != 0) {
            count++;
        }
        i++;
    }
    return count;
}

int main() {
    char str[] = "1010111";
    int rotations = countRotationsOfOddValueBinaryString(str);
    printf("Count of rotations of binary string with odd value: %d\n", rotations);
    return 0;
}