#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 4096U

char *longest_common_prefix(const char *const *strs, size_t count)
{
    if (strs == NULL || count == 0U) {
        return NULL;
    }

    for (size_t i = 0U; i < count; i++) {
        if (strs[i] == NULL) {
            return NULL;
        }
    }

    size_t prefix_len = strnlen(strs[0], MAX_STRING_LEN);
    if (prefix_len == MAX_STRING_LEN) {
        return NULL;
    }

    for (size_t i = 1U; i < count; i++) {
        size_t j = 0U;
        while (j < prefix_len && strs[i][j] != '\0' && strs[i][j] == strs[0][j]) {
            j++;
        }
        prefix_len = j;
        if (prefix_len == 0U) {
            break;
        }
    }

    char *result = malloc(prefix_len + 1U);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, strs[0], prefix_len);
    result[prefix_len] = '\0';

    return result;
}

int main(void)
{
    const char *const strings[] = {
        "flower",
        "flow",
        "flight"
    };
    size_t count = sizeof(strings) / sizeof(strings[0]);

    char *prefix = longest_common_prefix(strings, count);
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