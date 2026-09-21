#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

static bool bounded_string_length(const char *string, size_t maximum,
                                  size_t *length)
{
    const char *terminator;

    if (string == NULL || length == NULL) {
        return false;
    }

    terminator = memchr(string, '\0', maximum);
    if (terminator == NULL) {
        return false;
    }

    *length = (size_t)(terminator - string);
    return true;
}

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

static bool concatenate_adjacent(const char *const input[], size_t count,
                                 size_t maximum_string_length,
                                 char ***output, size_t *output_count)
{
    char **result;
    size_t result_count;

    if (output == NULL || output_count == NULL) {
        return false;
    }

    *output = NULL;
    *output_count = 0;

    if (input == NULL || count < 2 || maximum_string_length == 0) {
        return false;
    }

    result_count = count - 1;

    if (result_count > SIZE_MAX / sizeof(*result)) {
        return false;
    }

    result = calloc(result_count, sizeof(*result));
    if (result == NULL) {
        return false;
    }

    for (size_t i = 0; i < result_count; ++i) {
        size_t first_length;
        size_t second_length;
        size_t allocation_size;

        if (!bounded_string_length(input[i], maximum_string_length,
                                   &first_length) ||
            !bounded_string_length(input[i + 1], maximum_string_length,
                                   &second_length)) {
            free_strings(result, result_count);
            return false;
        }

        if (first_length > SIZE_MAX - second_length ||
            first_length + second_length == SIZE_MAX) {
            free_strings(result, result_count);
            return false;
        }

        allocation_size = first_length + second_length + 1;
        result[i] = malloc(allocation_size);
        if (result[i] == NULL) {
            free_strings(result, result_count);
            return false;
        }

        if (first_length != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[i], input[i], first_length);
        }

        if (second_length != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[i] + first_length, input[i + 1], second_length);
        }

        result[i][first_length + second_length] = '\0';
    }

    *output = result;
    *output_count = result_count;
    return true;
}

int main(void)
{
    const char *tuple[] = {"a", "b", "c", "d"};
    const size_t tuple_count = sizeof(tuple) / sizeof(tuple[0]);
    const size_t maximum_string_length = 1024;
    char **result = NULL;
    size_t result_count = 0;

    if (!concatenate_adjacent(tuple, tuple_count, maximum_string_length,
                              &result, &result_count)) {
        fputs("Failed to concatenate adjacent elements.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result_count; ++i) {
        if (printf("%s%s", result[i],
                   i + 1 < result_count ? " " : "\n") < 0) {
            free_strings(result, result_count);
            return EXIT_FAILURE;
        }
    }

    free_strings(result, result_count);
    return EXIT_SUCCESS;
}