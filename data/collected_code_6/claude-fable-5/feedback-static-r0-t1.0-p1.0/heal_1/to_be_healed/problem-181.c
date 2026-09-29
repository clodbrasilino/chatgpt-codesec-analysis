#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longest_common_prefix(const char *const *strs, size_t count)
{
    char *prefix = NULL;
    size_t prefix_len = 0;
    size_t i;

    if (strs == NULL || count == 0) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (strs[i] == NULL) {
            return NULL;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    prefix_len = strlen(strs[0]);

    for (i = 1; i < count; i++) {
        size_t j = 0;
        while (j < prefix_len && strs[i][j] != '\0' && strs[i][j] == strs[0][j]) {
            j++;
        }
        prefix_len = j;
        if (prefix_len == 0) {
            break;
        }
    }

    prefix = malloc(prefix_len + 1);
    if (prefix == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(prefix, strs[0], prefix_len);
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