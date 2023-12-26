#include <stdio.h>
#include <string.h>

void splitStringAtUppercase(char* str) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int len = strlen(str);
    for(int i = 0; i < len; i++) {
        if(str[i] >= 'A' && str[i] <= 'Z') {
            printf("\n");
        }
        printf("%c", str[i]);
    }
}

int main() {
    char str[] = "SplitThisStringAtUppercase";
    splitStringAtUppercase(str);
    return 0;
}