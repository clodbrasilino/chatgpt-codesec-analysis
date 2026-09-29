#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longestCommonPrefix(char** strs, int strsSize) {
    if (strsSize <= 0 || strs == NULL) {
        char* empty = (char*)malloc(1);
        if (empty != NULL) empty[0] = '\0';
        return empty;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t minLen = strlen(strs[0]);
    for (int i = 1; i < strsSize; i++) {
        if (strs[i] == NULL) {
            char* empty = (char*)malloc(1);
            if (empty != NULL) empty[0] = '\0';
            return empty;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t currentLen = strlen(strs[i]);
        if (currentLen < minLen) {
            minLen = currentLen;
        }
    }

    size_t prefixLen = 0;
    for (size_t i = 0; i < minLen; i++) {
        char currentChar = strs[0][i];
        for (int j = 1; j < strsSize; j++) {
            if (strs[j][i] != currentChar) {
                char* prefix = (char*)malloc(prefixLen + 1);
                if (prefix != NULL) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(prefix, strs[0], prefixLen);
                    prefix[prefixLen] = '\0';
                }
                return prefix;
            }
        }
        prefixLen++;
    }

    char* prefix = (char*)malloc(prefixLen + 1);
    if (prefix != NULL) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(prefix, strs[0], prefixLen);
        prefix[prefixLen] = '\0';
    }
    return prefix;
}

int main() {
    char* strs[] = {"flower", "flow", "flight"};
    int size = sizeof(strs) / sizeof(strs[0]);

    char* result = longestCommonPrefix(strs, size);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    char* strs2[] = {"dog", "racecar", "car"};
    int size2 = sizeof(strs2) / sizeof(strs2[0]);

    char* result2 = longestCommonPrefix(strs2, size2);
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    return 0;
}