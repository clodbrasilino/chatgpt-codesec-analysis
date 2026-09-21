#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longest_common_prefix(const char *const strings[], size_t count)
{
    size_t prefix_length = 0U;
    char *prefix;

    if (strings == NULL || count == 0U || strings[0] == NULL) {
        return NULL;
    }

    while (strings[0][prefix_length] != '\0') {
        if (prefix_length == SIZE_MAX - 1U) {
            return NULL;
        }
        ++prefix_length;
    }

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

    prefix = malloc(prefix_length + 1U);
    if (prefix == NULL) {
        return NULL;
    }

    if (prefix_length != 0U) {
        memcpy(prefix, strings[0], prefix_length);
    }
    prefix[prefix_length] = '\0';

    return prefix;
}

int main(void)
{
    const char *strings[] = {"flower", "flow", "flight"};
    const size_t count = sizeof strings / sizeof strings[0];
    char *prefix = longest_common_prefix(strings, count);

    if (prefix == NULL) {
        fputs("Failed to find the longest common prefix.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", prefix) < 0) {
        free(prefix);
        return EXIT_FAILURE;
    }

    free(prefix);
    return EXIT_SUCCESS;
}