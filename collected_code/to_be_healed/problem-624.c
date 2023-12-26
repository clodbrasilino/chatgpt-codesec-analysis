#include <stdio.h>
#include <ctype.h>
#include <string.h>

void convertToUpper(char* str) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        str[i] = toupper(str[i]);
    }
}

int main() {
    char str[] = "Hello, World!";
    convertToUpper(str);
    printf("%s\n", str);
    return 0;
}