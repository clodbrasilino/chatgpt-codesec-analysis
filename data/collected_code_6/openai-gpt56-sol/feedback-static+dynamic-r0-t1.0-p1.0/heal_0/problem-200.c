#include <stdio.h>
#include <stdlib.h>

int find_max_indices(const int *values, size_t count, size_t **indices, size_t *index_count)
{
    size_t *result;
    size_t found;
    size_t i;
    int maximum;

    if (values == NULL || indices == NULL || index_count == NULL || count == 0) {
        return -1;
    }

    if (count > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    maximum = values[0];
    found = 1;
    result[0] = 0;

    for (i = 1; i < count; ++i) {
        if (values[i] > maximum) {
            maximum = values[i];
            found = 1;
            result[0] = i;
        } else if (values[i] == maximum) {
            result[found++] = i;
        }
    }

    *indices = result;
    *index_count = found;
    return 0;
}

int main(void)
{
    const int values[] = {4, 9, 2, 9, 7, 9};
    const size_t count = sizeof(values) / sizeof(values[0]);
    size_t *indices = NULL;
    size_t index_count = 0;
    size_t i;

    if (find_max_indices(values, count, &indices, &index_count) != 0) {
        fputs("Unable to find maximum value indices.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < index_count; ++i) {
        printf("%zu%s", indices[i], i + 1 == index_count ? "\n" : " ");
    }

    free(indices);
    return EXIT_SUCCESS;
}