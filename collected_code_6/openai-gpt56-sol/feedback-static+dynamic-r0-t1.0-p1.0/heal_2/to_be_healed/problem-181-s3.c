#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longest_common_prefix(const char *const strings[], size_t count)
{
    size_t prefix_length;
    char *prefix;

    if (strings == NULL || count == 0U || strings[0] == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    prefix_length = strlen(strings[0]);

    for (size_t i = 1U; i < count; ++i) {
        size_t j = 0U;

        if (strings[i] == NULL) {
            return NULL;
        }

        while (j < prefix_length &&
               strings[i][j] != '\0' &&
               strings[0][j] == strings[i][j]) {
            ++j;
        }

        prefix_length = j;

        if (prefix_length == 0U) {
            break;
        }
    }

    if (prefix_length > SIZE_MAX - 1U) {
        return NULL;
    }

    prefix = malloc(prefix_length + 1U);
    if (prefix == NULL) {
        return NULL;
    }

    if (prefix_length != 0U) {
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