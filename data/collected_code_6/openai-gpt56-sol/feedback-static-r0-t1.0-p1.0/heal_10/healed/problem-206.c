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
                                size_t **result_lengths,
                                size_t *result_count)
{
    char **output = NULL;
    size_t *output_lengths = NULL;
    size_t initialized = 0;

    if (result == NULL || result_lengths == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_lengths = NULL;
    *result_count = 0;

    if (count < 2) {
        return 0;
    }

    if (tuple == NULL || lengths == NULL) {
        return -1;
    }

    const size_t output_count = count - 1;

    if (output_count > SIZE_MAX / sizeof(*output) ||
        output_count > SIZE_MAX / sizeof(*output_lengths)) {
        return -1;
    }

    output = calloc(output_count, sizeof(*output));
    if (output == NULL) {
        return -1;
    }

    output_lengths = calloc(output_count, sizeof(*output_lengths));
    if (output_lengths == NULL) {
        free(output);
        return -1;
    }

    for (size_t i = 0; i < output_count; ++i) {
        size_t first_length;
        size_t second_length;
        size_t combined_length;
        size_t allocation_size;
        char *joined;

        if (tuple[i] == NULL || tuple[i + 1] == NULL) {
            goto failure;
        }

        first_length = lengths[i];
        second_length = lengths[i + 1];

        if (first_length > SIZE_MAX - second_length) {
            goto failure;
        }

        combined_length = first_length + second_length;

        if (combined_length == SIZE_MAX) {
            goto failure;
        }

        allocation_size = combined_length + 1;
        joined = malloc(allocation_size);
        if (joined == NULL) {
            goto failure;
        }

        if (first_length > combined_length ||
            second_length > combined_length - first_length) {
            free(joined);
            goto failure;
        }

        if (first_length != 0) {
            memcpy(joined, tuple[i], first_length);
        }

        if (second_length != 0) {
            memcpy(joined + first_length, tuple[i + 1], second_length);
        }

        joined[combined_length] = '\0';
        output[i] = joined;
        output_lengths[i] = combined_length;
        initialized++;
    }

    *result = output;
    *result_lengths = output_lengths;
    *result_count = output_count;

    return 0;

failure:
    free(output_lengths);
    free_strings(output, initialized);
    return -1;
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
    char **result = NULL;
    size_t *result_lengths = NULL;
    size_t result_count = 0;

    if (tuple_count != lengths_count) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (concatenate_adjacent(tuple, lengths, tuple_count, &result,
                             &result_lengths, &result_count) != 0) {
        fputs("Failed to concatenate adjacent elements.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result_count; ++i) {
        if (fwrite(result[i], 1, result_lengths[i], stdout) !=
                result_lengths[i] ||
            fputc(i + 1 < result_count ? ' ' : '\n', stdout) == EOF) {
            free(result_lengths);
            free_strings(result, result_count);
            return EXIT_FAILURE;
        }
    }

    free(result_lengths);
    free_strings(result, result_count);

    return EXIT_SUCCESS;
}