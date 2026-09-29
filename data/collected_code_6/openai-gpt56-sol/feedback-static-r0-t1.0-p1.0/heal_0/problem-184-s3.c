#include <stdio.h>
#include <stdlib.h>

static int find_greater_values(const int *values,
                               size_t count,
                               int threshold,
                               int **result,
                               size_t *result_count)
{
    size_t matches = 0;
    size_t index;
    int *output;

    if (values == NULL || result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    for (index = 0; index < count; ++index) {
        if (values[index] > threshold) {
            ++matches;
        }
    }

    if (matches == 0) {
        return 0;
    }

    if (matches > SIZE_MAX / sizeof(*output)) {
        return -1;
    }

    output = malloc(matches * sizeof(*output));
    if (output == NULL) {
        return -1;
    }

    matches = 0;

    for (index = 0; index < count; ++index) {
        if (values[index] > threshold) {
            output[matches++] = values[index];
        }
    }

    *result = output;
    *result_count = matches;

    return 0;
}

int main(void)
{
    const int values[] = {3, 12, 7, 20, 5, 15};
    const size_t value_count = sizeof(values) / sizeof(values[0]);
    const int threshold = 10;
    int *result = NULL;
    size_t result_count = 0;
    size_t index;

    if (find_greater_values(values,
                            value_count,
                            threshold,
                            &result,
                            &result_count) != 0) {
        fputs("Failed to find matching values.\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0; index < result_count; ++index) {
        if (printf("%d\n", result[index]) < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);

    if (ferror(stdout)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}