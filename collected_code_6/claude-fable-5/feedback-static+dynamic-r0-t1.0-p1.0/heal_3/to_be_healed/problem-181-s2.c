#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longest_common_prefix(const char *const *strs, size_t count)
{
    size_t prefix_len;
    size_t alloc_len;
    size_t i;
    char *result;

    if (strs == NULL || count == 0U) {
        return NULL;
    }

    for (i = 0U; i < count; i++) {
        if (strs[i] == NULL) {
            return NULL;
        }
    }

    prefix_len = 0U;
    while (strs[0][prefix_len] != '\0') {
        prefix_len++;
    }

    for (i = 1U; i < count; i++) {
        size_t j = 0U;
        while (j < prefix_len && strs[i][j] != '\0' && strs[i][j] == strs[0][j]) {
            j++;
        }
        prefix_len = j;
        if (prefix_len == 0U) {
            break;
        }
    }

    if (prefix_len == (size_t)-1) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  alloc_len is assigned 'prefix_len+1U' here.
     */
    alloc_len = prefix_len + 1U;
    /* Possible weaknesses found:
     *  Condition 'alloc_len<prefix_len' is always false [knownConditionTrueFalse]
     *  Condition 'alloc_len<prefix_len' is always false
     */
    if (alloc_len < prefix_len) {
        return NULL;
    }

    result = malloc(alloc_len);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < prefix_len; i++) {
        result[i] = strs[0][i];
    }
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