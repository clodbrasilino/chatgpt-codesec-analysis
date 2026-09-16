#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longest_common_prefix(const char *const *strs, size_t count)
{
    size_t prefix_len;
    size_t i;
    char *result;

    if (strs == NULL || count == 0 || strs[0] == NULL) {
        return NULL;
    }

    prefix_len = strlen(strs[0]);

    for (i = 1; i < count; i++) {
        size_t j = 0;

        if (strs[i] == NULL) {
            return NULL;
        }

        while (j < prefix_len && strs[i][j] != '\0' && strs[i][j] == strs[0][j]) {
            j++;
        }
        prefix_len = j;

        if (prefix_len == 0) {
            break;
        }
    }

    result = malloc(prefix_len + 1);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, strs[0], prefix_len);
    result[prefix_len] = '\0';

    return result;
}

int main(void)
{
    const char *strings[] = { "flower", "flow", "flight" };
    size_t count = sizeof(strings) / sizeof(strings[0]);
    char *prefix;

    prefix = longest_common_prefix(strings, count);
    if (prefix == NULL) {
        if (fprintf(stderr, "Failed to compute longest common prefix\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Longest common prefix: \"%s\"\n", prefix) < 0) {
        free(prefix);
        return EXIT_FAILURE;
    }

    free(prefix);
    return EXIT_SUCCESS;
}