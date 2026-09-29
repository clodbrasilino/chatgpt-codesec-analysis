#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longest_common_prefix(const char *const strings[], size_t count)
{
    static const size_t max_string_length = 1024U * 1024U;
    size_t prefix_length;

    if (strings == NULL || count == 0U || strings[0] == NULL) {
        return NULL;
    }

    prefix_length = strnlen(strings[0], max_string_length);
    if (prefix_length == max_string_length) {
        return NULL;
    }

    for (size_t i = 1U; i < count; ++i) {
        size_t string_length;
        size_t comparison_length;
        size_t j = 0U;

        if (strings[i] == NULL) {
            return NULL;
        }

        string_length = strnlen(strings[i], max_string_length);
        if (string_length == max_string_length) {
            return NULL;
        }

        comparison_length = prefix_length < string_length
                                ? prefix_length
                                : string_length;

        while (j < comparison_length && strings[0][j] == strings[i][j]) {
            ++j;
        }

        prefix_length = j;

        if (prefix_length == 0U) {
            break;
        }
    }

    if (prefix_length == SIZE_MAX) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  allocation_size is assigned 'prefix_length+1U' here.
     */
    size_t allocation_size = prefix_length + 1U;
    char *prefix = malloc(allocation_size);

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (prefix == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition 'prefix_length>=allocation_size' is always false [knownConditionTrueFalse]
     *  Condition 'prefix_length>=allocation_size' is always false
     */
    if (prefix_length >= allocation_size) {
        free(prefix);
        return NULL;
    }

    if (prefix_length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(prefix, strings[0], prefix_length);
    }

    prefix[prefix_length] = '\0';
    return prefix;
}

int main(void)
{
    const char *strings[] = {
        "flower",
        "flow",
        "flight"
    };
    const size_t count = sizeof(strings) / sizeof(strings[0]);
    char *prefix = longest_common_prefix(strings, count);

    if (prefix == NULL) {
        fputs("Failed to determine the longest common prefix.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Longest common prefix: \"%s\"\n", prefix) < 0) {
        free(prefix);
        return EXIT_FAILURE;
    }

    free(prefix);
    return EXIT_SUCCESS;
}