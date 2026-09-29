#include <stdio.h>
#include <stdlib.h>

static int find_greater_values(const int *values, size_t count, int threshold,
                               int **result, size_t *result_count)
{
    size_t matches = 0;
    size_t index = 0;
    size_t output_index = 0;
    int *output = NULL;

    if (result == NULL || result_count == NULL ||
        (values == NULL && count != 0U)) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    for (index = 0; index < count; ++index) {
        if (values[index] > threshold) {
            ++matches;
        }
    }

    if (matches == 0U) {
        return 0;
    }

    if (matches > SIZE_MAX / sizeof(*output)) {
        return -1;
    }

    output = malloc(matches * sizeof(*output));
    if (output == NULL) {
        return -1;
    }

    for (index = 0; index < count; ++index) {
        if (values[index] > threshold) {
            output[output_index++] = values[index];
        }
    }

    *result = output;
    *result_count = matches;
    return 0;
}

int main(void)
{
    const int values[] = {3, 12, -4, 8, 21, 5, 14};
    const size_t value_count = sizeof(values) / sizeof(values[0]);
    const int threshold = 10;
    int *matches = NULL;
    size_t match_count = 0;
    size_t index = 0;

    if (find_greater_values(values, value_count, threshold,
                            &matches, &match_count) != 0) {
        fputs("Unable to find matching values.\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0; index < match_count; ++index) {
        if (printf("%d\n", matches[index]) < 0) {
            free(matches);
            return EXIT_FAILURE;
        }
    }

    free(matches);

    if (ferror(stdout) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}