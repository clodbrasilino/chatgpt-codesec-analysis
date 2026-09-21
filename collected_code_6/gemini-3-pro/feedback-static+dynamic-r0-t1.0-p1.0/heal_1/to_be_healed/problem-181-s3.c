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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int prefixLen = strlen(strs[0]);
    for (int i = 1; i < strsSize; i++) {
        int j = 0;
        while (j < prefixLen && strs[0][j] == strs[i][j]) {
            j++;
        }
        prefixLen = j;
        if (prefixLen == 0) {
            break;
        }
    }

    char* result = (char*)malloc(prefixLen + 1);
    if (!result) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(result, strs[0], prefixLen);
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