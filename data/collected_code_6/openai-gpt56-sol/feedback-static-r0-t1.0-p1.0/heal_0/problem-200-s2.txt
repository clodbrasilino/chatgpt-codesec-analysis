#include <stdio.h>
#include <stdlib.h>

int find_max_indices(const int *values, size_t count, size_t **indices, size_t *index_count)
{
    int maximum;
    size_t matches = 0;
    size_t *result;

    if (values == NULL || indices == NULL || index_count == NULL || count == 0) {
        return -1;
    }

    *indices = NULL;
    *index_count = 0;
    maximum = values[0];

    for (size_t i = 1; i < count; ++i) {
        if (values[i] > maximum) {
            maximum = values[i];
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (values[i] == maximum) {
            ++matches;
        }
    }

    if (matches > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = malloc(matches * sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    matches = 0;
    for (size_t i = 0; i < count; ++i) {
        if (values[i] == maximum) {
            result[matches++] = i;
        }
    }

    *indices = result;
    *index_count = matches;
    return 0;
}

int main(void)
{
    const int values[] = {4, 9, 2, 9, 7, 9};
    const size_t count = sizeof(values) / sizeof(values[0]);
    size_t *indices = NULL;
    size_t index_count = 0;

    if (find_max_indices(values, count, &indices, &index_count) != 0) {
        fputs("Unable to find maximum indices.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < index_count; ++i) {
        printf("%zu%s", indices[i], i + 1 == index_count ? "\n" : " ");
    }

    free(indices);
    return EXIT_SUCCESS;
}