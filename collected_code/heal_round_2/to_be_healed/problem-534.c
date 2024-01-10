#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isStringValid(const char* str) {
    while(*str) {
        if(*str++ == '\0') {
            return true;
        }
    }
    return false;
}

void searchString(const char* pattern, const char* str) {
    if(!(isStringValid(pattern) && isStringValid(str))) {
        printf("One or more strings are not null terminated \n");
        return;
    }

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int patternLength = strlen(pattern);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int strLength = strlen(str);
    int i, j;

    for (i = 0; i <= strLength - patternLength; i++) {
        for (j = 0; j < patternLength; j++) {
            if (str[i + j] != pattern[j]) {
                break;
            }
        }

        if (j == patternLength) {
            printf("Pattern found at index %d\n", i);
        }
    }
}

int main() {
    const char* str = "This is a test string";
    const char* pattern = "test";

    searchString(pattern, str);

    return 0;
}