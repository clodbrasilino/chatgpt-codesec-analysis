#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int find_max_indices(const int *values, size_t count,
                            size_t **indices, size_t *index_count)
{
    if (values == NULL || indices == NULL || index_count == NULL || count == 0) {
        return -1;
    }

    if (count > SIZE_MAX / sizeof(**indices)) {
        return -1;
    }

    size_t *result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    int maximum = values[0];
    size_t matches = 1;
    result[0] = 0;

    for (size_t i = 1; i < count; ++i) {
        if (values[i] > maximum) {
            maximum = values[i];
            matches = 1;
            result[0] = i;
        } else if (values[i] == maximum) {
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
        fputs("Failed to find maximum-value indices.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < index_count; ++i) {
        printf("%zu%s", indices[i], i + 1 < index_count ? " " : "\n");
    }

    free(indices);
    return EXIT_SUCCESS;
}