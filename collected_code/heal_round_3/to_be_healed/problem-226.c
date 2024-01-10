#include <stdio.h>
#include <string.h>

void removeOddIndexChars(char* str) {
    if (str == NULL) return;

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int length = strlen(str);
    int i, j;
    /* Possible weaknesses found:
     *  valid subscripts for 'str' are '[0]' to '[8]'
     *  stack-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
     *  use of uninitialized value '*str_16(D) + _7' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     *  read of 1 byte from after the end of 'str'
     */
    for (i = 0, j = 1; j < length && str[j] != '\0'; i++, j += 2) {
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