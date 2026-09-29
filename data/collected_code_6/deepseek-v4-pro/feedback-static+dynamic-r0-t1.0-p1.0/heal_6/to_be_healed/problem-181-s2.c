#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char* longestCommonPrefix(char** strs, int strsSize) {
    if (strs == NULL || strsSize <= 0) {
        char* empty = (char*)malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    if (strsSize == 1) {
        if (strs[0] == NULL) {
            char* empty = (char*)malloc(1);
            if (empty == NULL) {
                return NULL;
            }
            empty[0] = '\0';
            return empty;
        }
        size_t len = strnlen(strs[0], SIZE_MAX);
        char* result = (char*)malloc(len + 1);
        if (result == NULL) {
            return NULL;
        }
        if (len > 0) {
            if (len > SIZE_MAX - 1) {
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result, strs[0], len);
        }
        result[len] = '\0';
        return result;
    }

    if (strs[0] == NULL) {
        char* empty = (char*)malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    size_t minLen = strnlen(strs[0], SIZE_MAX);
    for (int i = 1; i < strsSize; ++i) {
        if (strs[i] == NULL) {
            minLen = 0;
            break;
        }
        size_t len = strnlen(strs[i], SIZE_MAX);
        if (len < minLen) {
            minLen = len;
        }
    }

    if (minLen == 0) {
        char* empty = (char*)malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    size_t prefixLen = 0;
    for (size_t i = 0; i < minLen; ++i) {
        char current = strs[0][i];
        int match = 1;
        for (int j = 1; j < strsSize; ++j) {
            if (strs[j][i] != current) {
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
    if (result == NULL) {
        return NULL;
    }
    if (prefixLen > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, strs[0], prefixLen);
    }
    result[prefixLen] = '\0';
    return result;
}

int main(void) {
    char* strings1[] = {"flower", "flow", "flight"};
    int size1 = sizeof(strings1) / sizeof(strings1[0]);
    char* prefix1 = longestCommonPrefix(strings1, size1);
    if (prefix1 != NULL) {
        printf("Common prefix: %s\n", prefix1);
        free(prefix1);
    }

    char* strings2[] = {"dog", "racecar", "car"};
    int size2 = sizeof(strings2) / sizeof(strings2[0]);
    char* prefix2 = longestCommonPrefix(strings2, size2);
    if (prefix2 != NULL) {
        printf("Common prefix: %s\n", prefix2);
        free(prefix2);
    }

    char* strings3[] = {"interspecies", "interstellar", "interstate"};
    int size3 = sizeof(strings3) / sizeof(strings3[0]);
    char* prefix3 = longestCommonPrefix(strings3, size3);
    if (prefix3 != NULL) {
        printf("Common prefix: %s\n", prefix3);
        free(prefix3);
    }

    char* strings4[] = {"", "b"};
    int size4 = sizeof(strings4) / sizeof(strings4[0]);
    char* prefix4 = longestCommonPrefix(strings4, size4);
    if (prefix4 != NULL) {
        printf("Common prefix: %s\n", prefix4);
        free(prefix4);
    }

    char* strings5[] = {"a"};
    int size5 = sizeof(strings5) / sizeof(strings5[0]);
    char* prefix5 = longestCommonPrefix(strings5, size5);
    if (prefix5 != NULL) {
        printf("Common prefix: %s\n", prefix5);
        free(prefix5);
    }

    char* prefix6 = longestCommonPrefix(NULL, 0);
    if (prefix6 != NULL) {
        printf("Common prefix: %s\n", prefix6);
        free(prefix6);
    }

    return 0;
}