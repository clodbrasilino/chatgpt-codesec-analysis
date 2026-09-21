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
    if (tuple == NULL || lengths == NULL ||
        result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (count < 2) {
        return 0;
    }

    if (count - 1 > SIZE_MAX / sizeof(char *)) {
        return -1;
    }

    char **output = calloc(count - 1, sizeof(*output));
    if (output == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count - 1; ++i) {
        if (tuple[i] == NULL || tuple[i + 1] == NULL) {
            free_strings(output, i);
            return -1;
        }

        size_t first_length = lengths[i];
        size_t second_length = lengths[i + 1];

        if (first_length > SIZE_MAX - second_length ||
            first_length + second_length == SIZE_MAX) {
            free_strings(output, i);
            return -1;
        }

        size_t combined_length = first_length + second_length;
        output[i] = malloc(combined_length + 1);
        if (output[i] == NULL) {
            free_strings(output, i);
            return -1;
        }

        if (first_length != 0) {
            memcpy(output[i], tuple[i], first_length);
        }

        if (second_length != 0) {
            memcpy(output[i] + first_length, tuple[i + 1], second_length);
        }

        output[i][combined_length] = '\0';
    }

    *result = output;
    *result_count = count - 1;
    return 0;
}

int main(void)
{
    const char *tuple[] = {"abc", "def", "ghi", "jkl"};
    const size_t lengths[] = {
        sizeof("abc") - 1,
        sizeof("def") - 1,
        sizeof("ghi") - 1,
        sizeof("jkl") - 1
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
        if (fwrite(result[i], 1, lengths[i] + lengths[i + 1], stdout) !=
            lengths[i] + lengths[i + 1] ||
            fputc(i + 1 < result_count ? ' ' : '\n', stdout) == EOF) {
            free_strings(result, result_count);
            return EXIT_FAILURE;
        }
    }

    free_strings(result, result_count);
    return EXIT_SUCCESS;
}