#include <stdio.h>
#include <string.h>

void removeEvenChars(char* str) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int len = strlen(str);
    int i, j;
    for (i = 0, j = 0; i < len; i += 2, j++)
        /* Possible weaknesses found:
         *  read of 1 byte from after the end of 'str'
         *  use of uninitialized value '*str_13(D) + _2' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         *  stack-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
         *  valid subscripts for 'str' are '[0]' to '[12]'
         */
        str[j] = str[i];
    str[j] = '\0';
}

int main() {
    char str[] = "Hello World!";
    removeEvenChars(str);
    printf("%s\n", str);
    return 0;
}