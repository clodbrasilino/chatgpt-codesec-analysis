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

    size_t output_count = count - 1;

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

        if (lengths[i] > SIZE_MAX - 1 ||
            lengths[i + 1] > SIZE_MAX - lengths[i] - 1) {
            free_strings(output, i);
            return -1;
        }

        size_t combined_length = lengths[i] + lengths[i + 1];
        size_t allocation_size = combined_length + 1;

        output[i] = malloc(allocation_size);
        if (output[i] == NULL) {
            free_strings(output, i);
            return -1;
        }

        if (lengths[i] != 0) {
            memcpy(output[i], tuple[i], lengths[i]);
        }

        if (lengths[i + 1] != 0) {
            memcpy(output[i] + lengths[i], tuple[i + 1], lengths[i + 1]);
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