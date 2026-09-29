#include <stdio.h>
#include <string.h>
#include <ctype.h>

int matchWordAtEnd(char* str, char* word) {
    int lenStr = strlen(str);
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