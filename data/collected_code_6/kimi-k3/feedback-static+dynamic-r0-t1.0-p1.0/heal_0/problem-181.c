#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longest_common_prefix(char **strs, int count)
{
    if (strs == NULL || count <= 0) {
        return NULL;
    }

    size_t prefix_len = strlen(strs[0]);

    for (int i = 1; i < count; i++) {
        size_t j = 0;
        while (j < prefix_len && strs[i][j] != '\0' && strs[0][j] == strs[i][j]) {
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

    memcpy(result, strs[0], prefix_len);
    result[prefix_len] = '\0';

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