#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    FIND_MIN_SUCCESS = 0,
    FIND_MIN_INVALID_ARGUMENT,
    FIND_MIN_ALLOCATION_FAILURE
} FindMinResult;

FindMinResult find_min_indices(const int *values, size_t length,
                               size_t **indices, size_t *index_count)
{
    int minimum;
    size_t count = 0;
    size_t position = 0;
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

    for (size_t i = 1; i < length; ++i) {
        if (values[i] < minimum) {
            minimum = values[i];
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (values[i] == minimum) {
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

    for (size_t i = 0; i < length; ++i) {
        if (values[i] == minimum) {
            result[position++] = i;
        }
    }

    *indices = result;
    *index_count = count;

    return FIND_MIN_SUCCESS;
}

int main(void)
{
    const int values[] = {7, 2, 5, 2, 9, 2, 4};
    const size_t length = sizeof(values) / sizeof(values[0]);
    size_t *indices = NULL;
    size_t index_count = 0;
    FindMinResult result;

    result = find_min_indices(values, length, &indices, &index_count);
    if (result != FIND_MIN_SUCCESS) {
        fprintf(stderr, "Unable to find minimum-value indices.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < index_count; ++i) {
        printf("%zu%s", indices[i], i + 1 == index_count ? "\n" : " ");
    }

    free(indices);
    indices = NULL;

    return EXIT_SUCCESS;
}