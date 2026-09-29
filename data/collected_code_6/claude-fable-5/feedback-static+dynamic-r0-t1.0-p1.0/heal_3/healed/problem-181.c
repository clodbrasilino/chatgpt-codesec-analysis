#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 4096

char *longest_common_prefix(const char *const *strs, size_t count)
{
    char *prefix = NULL;
    size_t prefix_len = 0;
    size_t alloc_size = 0;
    size_t i;

    if (strs == NULL || count == 0) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (strs[i] == NULL) {
            return NULL;
        }
    }

    prefix_len = strnlen(strs[0], MAX_STRING_LEN);
    if (prefix_len == MAX_STRING_LEN) {
        return NULL;
    }

    for (i = 1; i < count; i++) {
        size_t j = 0;
        size_t len = strnlen(strs[i], MAX_STRING_LEN);
        if (len == MAX_STRING_LEN) {
            return NULL;
        }
        while (j < prefix_len && j < len && strs[i][j] == strs[0][j]) {
            j++;
        }
        prefix_len = j;
        if (prefix_len == 0) {
            break;
        }
    }

    if (prefix_len >= MAX_STRING_LEN) {
        return NULL;
    }

    alloc_size = prefix_len + 1;

    prefix = malloc(alloc_size);
    if (prefix == NULL) {
        return NULL;
    }

    if (prefix_len > 0) {
        memcpy(prefix, strs[0], prefix_len);
    }
    prefix[prefix_len] = '\0';

    return prefix;
}

int main(void)
{
    const char *strings[] = {
        "flowering",
        "flower",
        "flow",
        "flourish"
    };
    size_t count = sizeof(strings) / sizeof(strings[0]);
    char *result;

    result = longest_common_prefix(strings, count);
    if (result == NULL) {
        fprintf(stderr, "Failed to compute longest common prefix\n");
        return EXIT_FAILURE;
    }

    if (printf("Longest common prefix: \"%s\"\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}