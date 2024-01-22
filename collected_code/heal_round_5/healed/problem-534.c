#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isStringValid(const char* str, int maxSize) {
    if(str == NULL) return false;

    for (int i = 0; i < maxSize; ++i) {
        if (str[i] == '\0') return true;
    }
    return false;
}

void searchString(const char* pattern, const char* str, int maxSize) {
    if(!(isStringValid(pattern, maxSize) && isStringValid(str, maxSize))) {
        printf("One or more strings are not null terminated \n");
        return;
    }

    int patternLength = strnlen(pattern, maxSize);
    int strLength = strnlen(str, maxSize);
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

#define MAX_SIZE 1000

int main() {
    const char* str = "This is a test string";
    const char* pattern = "test";
    searchString(pattern, str, MAX_SIZE);
    return 0;
}