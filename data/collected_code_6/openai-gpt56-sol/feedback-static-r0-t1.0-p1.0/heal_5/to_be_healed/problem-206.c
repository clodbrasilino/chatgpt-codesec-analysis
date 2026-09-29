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

static int concatenate_adjacent(const char *const tuple[],
                                const size_t lengths[],
                                size_t count,
                                char ***result,
                                size_t *result_count)
{
    if (result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (tuple == NULL || lengths == NULL) {
        return -1;
    }

    if (count < 2) {
        return 0;
    }

    const size_t output_count = count - 1;

    if (output_count > SIZE_MAX / sizeof(char *)) {
        return -1;
    }

    char **output = calloc(output_count, sizeof(*output));
    if (output == NULL) {
        return -1;
    }

    for (size_t i = 0; i < output_count; ++i) {
        if (tuple[i] == NULL || tuple[i + 1] == NULL) {
            free_strings(output, i);
            return -1;
        }

        const size_t first_length = lengths[i];
        const size_t second_length = lengths[i + 1];

        if (first_length > SIZE_MAX - second_length) {
            free_strings(output, i);
            return -1;
        }

        const size_t combined_length = first_length + second_length;

        if (combined_length == SIZE_MAX) {
            free_strings(output, i);
            return -1;
        }

        const size_t allocation_size = combined_length + 1;
        output[i] = malloc(allocation_size);
        if (output[i] == NULL) {
            free_strings(output, i);
            return -1;
        }

        size_t offset = 0;

        if (first_length > allocation_size - offset - 1) {
            free_strings(output, i + 1);
            return -1;
        }

        if (first_length != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output[i] + offset, tuple[i], first_length);
            offset += first_length;
        }

        if (second_length > allocation_size - offset - 1) {
            free_strings(output, i + 1);
            return -1;
        }

        if (second_length != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output[i] + offset, tuple[i + 1], second_length);
            offset += second_length;
        }

        output[i][offset] = '\0';
    }

    *result = output;
    *result_count = output_count;
    return 0;
}

int main(void)
{
    const char *tuple[] = {
        "abc",
        "def",
        "ghi",
        "jkl"
    };

    const size_t lengths[] = {
        sizeof("abc") - 1,
        sizeof("def") - 1,
        sizeof("ghi") - 1,
        sizeof("jkl") - 1
    };

    const size_t tuple_count = sizeof(tuple) / sizeof(tuple[0]);
    const size_t lengths_count = sizeof(lengths) / sizeof(lengths[0]);

    if (tuple_count != lengths_count) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    char **result = NULL;
    size_t result_count = 0;

    if (concatenate_adjacent(tuple, lengths, tuple_count,
                             &result, &result_count) != 0) {
        fputs("Failed to concatenate adjacent elements.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result_count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        const size_t output_length = strlen(result[i]);

        if (fwrite(result[i], 1, output_length, stdout) != output_length ||
            fputc(i + 1 < result_count ? ' ' : '\n', stdout) == EOF) {
            free_strings(result, result_count);
            return EXIT_FAILURE;
        }
    }

    free_strings(result, result_count);
    return EXIT_SUCCESS;
}