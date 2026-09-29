#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longest_common_prefix(const char *const *strs, size_t count)
{
    size_t prefix_len;
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'j' can be reduced. [variableScope]
     */
    size_t j;
    char *result;

    if (strs == NULL || count == 0U) {
        return NULL;
    }

    for (i = 0U; i < count; i++) {
        if (strs[i] == NULL) {
            return NULL;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    prefix_len = strlen(strs[0]);

    for (i = 1U; i < count; i++) {
        j = 0U;
        while (j < prefix_len && strs[i][j] != '\0' && strs[i][j] == strs[0][j]) {
            j++;
        }
        prefix_len = j;
        if (prefix_len == 0U) {
            break;
        }
    }

    result = malloc(prefix_len + 1U);
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
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