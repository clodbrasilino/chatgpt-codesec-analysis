#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_strings(char **strings, size_t count)
{
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(strings[i]);
    }

    free(strings);
}

static int extract_strings_by_length(const char *const input[],
                                     size_t input_count,
                                     size_t required_length,
                                     char ***output,
                                     size_t *output_count)
{
    char **result = NULL;
    size_t count = 0;
    size_t index = 0;

    if (output == NULL || output_count == NULL) {
        return -1;
    }

    *output = NULL;
    *output_count = 0;

    if (input_count != 0 && input == NULL) {
        return -1;
    }

    if (required_length == SIZE_MAX) {
        return -1;
    }

    for (size_t i = 0; i < input_count; ++i) {
        if (input[i] == NULL) {
            return -1;
        }

        if (strnlen(input[i], required_length + 1) == required_length) {
            if (count == SIZE_MAX) {
                return -1;
            }
            ++count;
        }
    }

    if (count == 0) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = calloc(count, sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < input_count; ++i) {
        size_t length = strnlen(input[i], required_length + 1);

        if (length == required_length) {
            result[index] = malloc(length + 1);
            if (result[index] == NULL) {
                free_strings(result, index);
                return -1;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[index], input[i], length);
            result[index][length] = '\0';
            ++index;
        }
    }

    *output = result;
    *output_count = index;
    return 0;
}

int main(void)
{
    const char *values[] = {
        "apple",
        "pear",
        "grape",
        "plum",
        "melon",
        "kiwi"
    };
    const size_t required_length = 5;
    const size_t value_count = sizeof(values) / sizeof(values[0]);
    char **matches = NULL;
    size_t match_count = 0;

    if (extract_strings_by_length(values,
                                  value_count,
                                  required_length,
                                  &matches,
                                  &match_count) != 0) {
        fputs("Failed to extract strings.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < match_count; ++i) {
        if (puts(matches[i]) == EOF) {
            free_strings(matches, match_count);
            return EXIT_FAILURE;
        }
    }

    free_strings(matches, match_count);
    return EXIT_SUCCESS;
}