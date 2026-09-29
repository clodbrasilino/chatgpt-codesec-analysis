#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longest_common_prefix(char **strs, int count)
{
    if (strs == NULL || count <= 0 || strs[0] == NULL) {
        return NULL;
    }

    size_t prefix_len = strnlen(strs[0], 1024);

    for (int i = 1; i < count; i++) {
        if (strs[i] == NULL) {
            prefix_len = 0;
            break;
        }
        size_t j = 0;
        while (j < prefix_len && strs[i][j] != '\0' && strs[0][j] == strs[i][j]) {
            j++;
        }
        prefix_len = j;
        if (prefix_len == 0) {
            break;
        }
    }

    if (prefix_len == 0) {
        char *result = (char *)malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    size_t copy_len = strnlen(strs[0], prefix_len);
    if (copy_len > prefix_len) {
        copy_len = prefix_len;
    }

    char *result = (char *)malloc(copy_len + 1);
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(result, strs[0], copy_len);
    result[copy_len] = '\0';

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