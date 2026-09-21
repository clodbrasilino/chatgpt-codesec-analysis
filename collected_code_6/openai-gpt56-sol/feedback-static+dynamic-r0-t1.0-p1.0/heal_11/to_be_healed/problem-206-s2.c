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

static int validate_string(const char *string, size_t length)
{
    if (string == NULL || length == SIZE_MAX) {
        return -1;
    }

    return memchr(string, '\0', length + 1) == string + length ? 0 : -1;
}

static int concatenate_adjacent(const char *const items[],
                                const size_t lengths[],
                                size_t count,
                                char ***result,
                                size_t *result_count)
{
    char **output;
    size_t output_count;

    if (result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (count < 2) {
        return 0;
    }

    if (items == NULL || lengths == NULL) {
        return -1;
    }

    output_count = count - 1;

    if (output_count > SIZE_MAX / sizeof(*output)) {
        return -1;
    }

    output = calloc(output_count, sizeof(*output));
    if (output == NULL) {
        return -1;
    }

    for (size_t i = 0; i < output_count; ++i) {
        size_t first_length = lengths[i];
        size_t second_length = lengths[i + 1];
        size_t combined_length;
        size_t allocation_size;

        if (validate_string(items[i], first_length) != 0 ||
            validate_string(items[i + 1], second_length) != 0) {
            free_strings(output, output_count);
            return -1;
        }

        if (first_length > SIZE_MAX - second_length) {
            free_strings(output, output_count);
            return -1;
        }

        combined_length = first_length + second_length;

        if (combined_length == SIZE_MAX) {
            free_strings(output, output_count);
            return -1;
        }

        allocation_size = combined_length + 1;
        output[i] = malloc(allocation_size);
        if (output[i] == NULL) {
            free_strings(output, output_count);
            return -1;
        }

        if (first_length != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output[i], items[i], first_length);
        }

        if (second_length != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output[i] + first_length, items[i + 1], second_length);
        }

        output[i][combined_length] = '\0';
    }

    *result = output;
    *result_count = output_count;
    return 0;
}

int main(void)
{
    const char *tuple[] = {"ab", "cd", "ef", "gh"};
    const size_t lengths[] = {
        sizeof("ab") - 1,
        sizeof("cd") - 1,
        sizeof("ef") - 1,
        sizeof("gh") - 1
    };
    const size_t tuple_count = sizeof(tuple) / sizeof(tuple[0]);
    char **result = NULL;
    size_t result_count = 0;

    if (concatenate_adjacent(tuple, lengths, tuple_count,
                             &result, &result_count) != 0) {
        fputs("Failed to concatenate adjacent elements.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result_count; ++i) {
        if (printf("%s\n", result[i]) < 0) {
            free_strings(result, result_count);
            return EXIT_FAILURE;
        }
    }

    free_strings(result, result_count);
    return EXIT_SUCCESS;
}