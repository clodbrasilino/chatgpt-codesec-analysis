#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int concatenate_adjacent(const char *const items[],
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

    if (items == NULL) {
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
        int required;
        size_t allocation_size;

        if (items[i] == NULL || items[i + 1] == NULL) {
            goto failure;
        }

        required = snprintf(NULL, 0, "%s%s", items[i], items[i + 1]);
        if (required < 0) {
            goto failure;
        }

        if ((size_t)required == SIZE_MAX) {
            goto failure;
        }

        allocation_size = (size_t)required + 1;
        output[i] = malloc(allocation_size);
        if (output[i] == NULL) {
            goto failure;
        }

        if (snprintf(output[i],
                     allocation_size,
                     "%s%s",
                     items[i],
                     items[i + 1]) != required) {
            goto failure;
        }
    }

    *result = output;
    *result_count = output_count;
    return 0;

failure:
    for (size_t i = 0; i < output_count; ++i) {
        free(output[i]);
    }

    free(output);
    return -1;
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

int main(void)
{
    const char *tuple[] = {"ab", "cd", "ef", "gh"};
    const size_t tuple_count = sizeof(tuple) / sizeof(tuple[0]);
    char **result = NULL;
    size_t result_count = 0;

    if (concatenate_adjacent(tuple, tuple_count,
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