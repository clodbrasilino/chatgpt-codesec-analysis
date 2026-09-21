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

    if (count < 2) {
        return 0;
    }

    if (tuple == NULL || lengths == NULL) {
        return -1;
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
        const char *left = tuple[i];
        const char *right = tuple[i + 1];
        const size_t left_length = lengths[i];
        const size_t right_length = lengths[i + 1];

        if (left == NULL || right == NULL) {
            free_strings(output, i);
            return -1;
        }

        if (left_length > SIZE_MAX - right_length ||
            left_length + right_length == SIZE_MAX) {
            free_strings(output, i);
            return -1;
        }

        const size_t combined_length = left_length + right_length;
        const size_t buffer_size = combined_length + 1;

        output[i] = malloc(buffer_size);
        if (output[i] == NULL) {
            free_strings(output, i);
            return -1;
        }

        if (left_length > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output[i], left, left_length);
        }

        if (right_length > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output[i] + left_length, right, right_length);
        }

        output[i][combined_length] = '\0';
    }

    *result = output;
    *result_count = output_count;
    return 0;
}

int main(void)
{
    static const char first[] = "abc";
    static const char second[] = "def";
    static const char third[] = "ghi";
    static const char fourth[] = "jkl";

    const char *tuple[] = {
        first,
        second,
        third,
        fourth
    };

    const size_t lengths[] = {
        sizeof(first) - 1,
        sizeof(second) - 1,
        sizeof(third) - 1,
        sizeof(fourth) - 1
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
        if (fputs(result[i], stdout) == EOF ||
            fputc(i + 1 < result_count ? ' ' : '\n', stdout) == EOF) {
            free_strings(result, result_count);
            return EXIT_FAILURE;
        }
    }

    free_strings(result, result_count);
    return EXIT_SUCCESS;
}