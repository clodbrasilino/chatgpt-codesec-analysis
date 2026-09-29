#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char **extract_strings_by_length(const char *const strings[],
                                 size_t count,
                                 size_t length,
                                 size_t *result_count)
{
    char **result;
    size_t matches = 0;
    size_t index = 0;

    if (result_count == NULL) {
        return NULL;
    }

    *result_count = 0;

    if ((count != 0 && strings == NULL) || length == SIZE_MAX) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (strings[i] != NULL &&
            strnlen(strings[i], length + 1) == length) {
            if (matches == SIZE_MAX) {
                return NULL;
            }
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
        size_t destination_size;

        if (strings[i] == NULL) {
            continue;
        }

        source_length = strnlen(strings[i], length + 1);
        if (source_length != length) {
            continue;
        }

        if (source_length == SIZE_MAX) {
            free_string_list(result, index);
            return NULL;
        }

        destination_size = source_length + 1;
        result[index] = malloc(destination_size);
        if (result[index] == NULL) {
            free_string_list(result, index);
            return NULL;
        }

        if (snprintf(result[index], destination_size, "%s", strings[i]) < 0) {
            free(result[index]);
            result[index] = NULL;
            free_string_list(result, index);
            return NULL;
        }

        ++index;
    }

    *result_count = index;
    return result;
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
    char **results = extract_strings_by_length(
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