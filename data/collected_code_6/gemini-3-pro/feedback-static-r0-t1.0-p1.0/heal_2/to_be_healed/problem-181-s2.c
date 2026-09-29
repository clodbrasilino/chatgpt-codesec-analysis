#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longestCommonPrefix(char** strs, int strsSize) {
    if (strsSize == 0 || strs == NULL || strs[0] == NULL) {
        char* empty = (char*)malloc(1);
        if (empty) {
            empty[0] = '\0';
        }
        return empty;
    }

    int prefixLen = 0;
    while (strs[0][prefixLen] != '\0') {
        prefixLen++;
    }

    for (int i = 1; i < strsSize; i++) {
        if (strs[i] == NULL) {
            char* empty = (char*)malloc(1);
            if (empty) {
                empty[0] = '\0';
            }
            return empty;
        }
        int j = 0;
        /* Possible weaknesses found:
         *  Condition 'strs[i][j]!='\0'' is always true [knownConditionTrueFalse]
         */
        while (j < prefixLen && strs[0][j] == strs[i][j] && strs[0][j] != '\0' && strs[i][j] != '\0') {
            j++;
        }
        prefixLen = j;
        if (prefixLen == 0) {
            break;
        }
    }

    char* result = (char*)malloc((prefixLen + 1) * sizeof(char));
    if (result == NULL) {
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

    char* lcp = longestCommonPrefix(strs, strsSize);

    if (lcp != NULL) {
        printf("%s\n", lcp);
        free(lcp);
    }

    return 0;
}