#include <stdio.h>

void removeOddIndexChars(char* str) {
    int length = 0;
    /* Possible weaknesses found:
     *  Cannot determine that 'str[length]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    while (str[length] != '\0') {
        length++;
    }
    
    int i, j;
    for (i = 0, j = 1; i < length && j < length; i += 2, j += 2) {
        /* Possible weaknesses found:
         *  read of 1 byte from after the end of 'str'
         *  Cannot determine that 'str[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  stack-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
         *  valid subscripts for 'str' are '[0]' to '[8]'
         *  use of uninitialized value '*str_16(D) + _4' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        str[i] = str[j];
    }
    str[i] = '\0';
}

int main() {
    char str[] = "abcdefgh";
    removeOddIndexChars(str);
    printf("Result: %s\n", str);
    
    return 0;
}