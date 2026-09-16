#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool find_min_indices(const int *values, size_t length,
                      size_t **indices, size_t *index_count)
{
    int minimum;
    size_t count = 0;
    size_t position = 0;
    size_t *result;

    if (indices == NULL || index_count == NULL) {
        return false;
    }

    *indices = NULL;
    *index_count = 0;

    if (values == NULL || length == 0) {
        return false;
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
        return false;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        if (values[i] == minimum) {
            result[position++] = i;
        }
    }

    *indices = result;
    *index_count = count;

    return true;
}

int main(void)
{
    const int values[] = {4, 2, 7, -1, 3, -1, 8};
    const size_t length = sizeof(values) / sizeof(values[0]);
    size_t *indices = NULL;
    size_t index_count = 0;

    if (!find_min_indices(values, length, &indices, &index_count)) {
        fputs("Failed to find minimum indices.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < index_count; ++i) {
        if (printf("%zu%s", indices[i],
                   i + 1 < index_count ? " " : "\n") < 0) {
            free(indices);
            return EXIT_FAILURE;
        }
    }

    free(indices);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}