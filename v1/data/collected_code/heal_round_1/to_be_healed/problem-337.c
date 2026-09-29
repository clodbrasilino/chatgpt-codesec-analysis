#include <stdio.h>
#include <string.h>
#include <ctype.h>

int matchWordAtEnd(char* str, char* word) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int lenStr = strlen(str);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'word[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int lenWord = strlen(word);
    int i, j;

    if (lenWord > lenStr) {
        return 0;
    }

    for (i = lenStr - lenWord, j = 0; i < lenStr; i++, j++) {
        if (tolower(str[i]) != tolower(word[j])) {
            return 0;
        }
    }

    if (isalpha(str[lenStr - lenWord - 1]) || isdigit(str[lenStr - lenWord - 1])) {
        return 0;
    }

    return 1;
}