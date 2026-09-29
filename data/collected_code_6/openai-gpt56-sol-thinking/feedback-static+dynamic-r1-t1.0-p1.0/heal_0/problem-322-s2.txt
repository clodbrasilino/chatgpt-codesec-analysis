#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    FIND_MIN_SUCCESS = 0,
    FIND_MIN_INVALID_ARGUMENT,
    FIND_MIN_ALLOCATION_FAILURE
} FindMinStatus;

FindMinStatus find_min_indices(const int *values, size_t length,
                               size_t **indices, size_t *index_count)
{
    int minimum;
    size_t count = 0;
    size_t position;
    size_t output_position = 0;
    size_t *result;

    if (indices == NULL || index_count == NULL) {
        return FIND_MIN_INVALID_ARGUMENT;
    }

    *indices = NULL;
    *index_count = 0;

    if (values == NULL || length == 0) {
        return FIND_MIN_INVALID_ARGUMENT;
    }

    minimum = values[0];

    for (position = 1; position < length; ++position) {
        if (values[position] < minimum) {
            minimum = values[position];
        }
    }

    for (position = 0; position < length; ++position) {
        if (values[position] == minimum) {
            ++count;
        }
    }

    if (count > SIZE_MAX / sizeof(*result)) {
        return FIND_MIN_ALLOCATION_FAILURE;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return FIND_MIN_ALLOCATION_FAILURE;
    }

    for (position = 0; position < length; ++position) {
        if (values[position] == minimum) {
            result[output_position++] = position;
        }
    }

    *indices = result;
    *index_count = count;

    return FIND_MIN_SUCCESS;
}

int main(void)
{
    const int values[] = {4, 2, 7, 2, 9, 2};
    const size_t length = sizeof(values) / sizeof(values[0]);
    size_t *indices = NULL;
    size_t index_count = 0;
    size_t i;
    FindMinStatus status;

    status = find_min_indices(values, length, &indices, &index_count);
    if (status != FIND_MIN_SUCCESS) {
        if (fputs("Unable to find minimum-value indices.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (i = 0; i < index_count; ++i) {
        if (printf("%zu%s", indices[i],
                   i + 1 < index_count ? " " : "\n") < 0) {
            free(indices);
            return EXIT_FAILURE;
        }
    }

    free(indices);
    return EXIT_SUCCESS;
}