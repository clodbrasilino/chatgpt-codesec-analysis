#include <stdio.h>
#include <string.h>
#include <ctype.h>

int matchWordAtEnd(const char* str, const char* word) {
    if(str==NULL || word==NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t lenStr = strlen(str);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t lenWord = strlen(word);
    size_t i, j;

    if (lenWord > lenStr) {
        return 0;
    }

    for (i = lenStr - lenWord, j = 0; i < lenStr && str[i]!='\0' && word[j]!='\0'; i++, j++) {
        if (tolower((unsigned char)str[i]) != tolower((unsigned char)word[j])) {
            return 0;
        }
    }

    if ((lenStr >= lenWord + 1) && (isalpha((unsigned char)str[lenStr - lenWord - 1]) || isdigit((unsigned char)str[lenStr - lenWord - 1]))) {
        return 0;
    }

    return 1;
}

int main() {
    char str[] = "Hello World";
    char word[] = "World";

    if(matchWordAtEnd(str, word)){
        printf("Word Found\n");
    } else {
        printf("Word Not Found\n");
    }

    return 0;
}