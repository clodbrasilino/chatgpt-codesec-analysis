#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longest_common_prefix(char **strs, int count)
{
    if (strs == NULL || count <= 0) {
        return NULL;
    }

    if (strs[0] == NULL) {
        return NULL;
    }

    size_t prefix_len = strnlen(strs[0], 256);

    for (int i = 1; i < count; i++) {
        if (strs[i] == NULL) {
            prefix_len = 0;
            break;
        }

        size_t j = 0;
        while (j < prefix_len && j < 256 && strs[i][j] != '\0' && strs[0][j] == strs[i][j]) {
            j++;
        }
        prefix_len = j;
        if (prefix_len == 0) {
            break;
        }
    }

    char *result = (char *)malloc(prefix_len + 1);
    if (result == NULL) {
        return NULL;
    }

    if (prefix_len > 0) {
        size_t src_len = strnlen(strs[0], 256);
        /* Possible weaknesses found:
         *  copy_len is assigned 'prefix_len<src_len?prefix_len:src_len' here.
         */
        size_t copy_len = prefix_len < src_len ? prefix_len : src_len;
        /* Possible weaknesses found:
         *  Condition 'copy_len>prefix_len' is always true [knownConditionTrueFalse]
         *  Condition 'copy_len>prefix_len' is always true
         */
        if (copy_len > prefix_len) {
            copy_len = prefix_len;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, strs[0], copy_len);
        result[copy_len] = '\0';
    } else {
        result[0] = '\0';
    }

    return result;
}

int main(void)
{
    char *strs[] = {"flower", "flow", "flight"};
    int count = sizeof(strs) / sizeof(strs[0]);

    char *prefix = longest_common_prefix(strs, count);
    if (prefix != NULL) {
        printf("Longest common prefix: %s\n", prefix);
        free(prefix);
    } else {
        printf("No common prefix found.\n");
    }

    return 0;
}