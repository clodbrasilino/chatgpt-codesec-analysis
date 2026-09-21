#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longestCommonPrefix(char** strs, int strsSize) {
    if (strsSize == 0) {
        char* empty = (char*)malloc(1);
        if (empty) {
            empty[0] = '\0';
        }
        return empty;
    }

    int prefixLen = 0;
    while (1) {
        char c = strs[0][prefixLen];
        if (c == '\0') {
            break;
        }
        
        int match = 1;
        for (int i = 1; i < strsSize; i++) {
            if (strs[i][prefixLen] != c) {
                match = 0;
                break;
            }
        }
        
        if (!match) {
            break;
        }
        prefixLen++;
    }

    char* result = (char*)malloc(prefixLen + 1);
    if (!result) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, strs[0], prefixLen);
    result[prefixLen] = '\0';

    return result;
}

int main(void) {
    char* strs[] = {"flower", "flow", "flight"};
    int strsSize = sizeof(strs) / sizeof(strs[0]);

    char* result = longestCommonPrefix(strs, strsSize);
    if (result) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}