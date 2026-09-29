#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_strings_by_length(const char *const strings[],
                                 size_t count,
                                 size_t length,
                                 size_t *result_count)
{
    char **result = NULL;
    size_t matches = 0;
    size_t index = 0;

    if (result_count == NULL) {
        return NULL;
    }

    *result_count = 0;

    if ((count > 0 && strings == NULL) || length == SIZE_MAX) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (strings[i] != NULL &&
            strnlen(strings[i], length + 1) == length) {
            ++matches;
        }
    }

    if (matches == 0 || matches > SIZE_MAX / sizeof(*result)) {
        return NULL;
    }

    result = calloc(matches, sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        size_t source_length;

        if (strings[i] == NULL) {
            continue;
        }

        source_length = strnlen(strings[i], length + 1);
        if (source_length != length) {
            continue;
        }

        result[index] = malloc(source_length + 1);
        if (result[index] == NULL) {
            for (size_t j = 0; j < index; ++j) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[index], strings[i], source_length);
        result[index][source_length] = '\0';
        ++index;
    }

    *result_count = index;
    return result;
}

void free_string_list(char **strings, size_t count)
{
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(strings[i]);
    }

    free(strings);
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
    const size_t target_length = 5;
    size_t result_count = 0;
    char **results;

    results = extract_strings_by_length(
        values,
        sizeof(values) / sizeof(values[0]),
        target_length,
        &result_count
    );

    if (results == NULL) {
        return result_count == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
    }

    for (size_t i = 0; i < result_count; ++i) {
        if (printf("%s\n", results[i]) < 0) {
            free_string_list(results, result_count);
            return EXIT_FAILURE;
        }
    }

    free_string_list(results, result_count);
    return EXIT_SUCCESS;
}