#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkSequence(const char *str, const char **patterns, size_t numPatterns) {
    if (str == NULL || patterns == NULL) {
        return 0;
    }

    size_t strLen = strlen(str);
    size_t currentPos = 0;

    for (size_t i = 0; i < numPatterns; i++) {
        if (patterns[i] == NULL) {
            return 0;
        }

        size_t patternLen = strlen(patterns[i]);
        if (patternLen == 0) {
            continue;
        }

        if (currentPos + patternLen > strLen) {
            return 0;
        }

        if (strncmp(str + currentPos, patterns[i], patternLen) != 0) {
            return 0;
        }

        currentPos += patternLen;
    }

    return currentPos == strLen;
}

int main(void) {
    const char *str1 = "applebananacherry";
    const char *patterns1[] = {"apple", "banana", "cherry"};
    size_t numPatterns1 = sizeof(patterns1) / sizeof(patterns1[0]);

    if (checkSequence(str1, patterns1, numPatterns1)) {
        printf("Test 1 Passed\n");
    } else {
        printf("Test 1 Failed\n");
    }

    const char *str2 = "applebananacherry";
    const char *patterns2[] = {"apple", "cherry", "banana"};
    size_t numPatterns2 = sizeof(patterns2) / sizeof(patterns2[0]);

    if (!checkSequence(str2, patterns2, numPatterns2)) {
        printf("Test 2 Passed\n");
    } else {
        printf("Test 2 Failed\n");
    }
    
    return 0;
}