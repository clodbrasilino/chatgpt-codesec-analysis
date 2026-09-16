#include <stdio.h>
#include <stdlib.h>

static int xor_tuples(const int *tuples, size_t tuple_count, size_t tuple_size, int *results)
{
    size_t i;
    size_t j;

    if (tuples == NULL || results == NULL || tuple_count == 0U || tuple_size == 0U) {
        return -1;
    }

    if (tuple_count > SIZE_MAX / tuple_size) {
        return -1;
    }

    for (i = 0U; i < tuple_count; ++i) {
        int value = 0;

        for (j = 0U; j < tuple_size; ++j) {
            value ^= tuples[i * tuple_size + j];
        }

        results[i] = value;
    }

    return 0;
}

int main(void)
{
    const int tuples[][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    const size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    const size_t tuple_size = sizeof(tuples[0]) / sizeof(tuples[0][0]);
    int *results;
    size_t i;
    int status;

    if (tuple_count > SIZE_MAX / sizeof(*results)) {
        return EXIT_FAILURE;
    }

    results = malloc(tuple_count * sizeof(*results));
    if (results == NULL) {
        return EXIT_FAILURE;
    }

    status = xor_tuples(&tuples[0][0], tuple_count, tuple_size, results);
    if (status != 0) {
        free(results);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < tuple_count; ++i) {
        if (printf("%d\n", results[i]) < 0) {
            free(results);
            return EXIT_FAILURE;
        }
    }

    free(results);
    return EXIT_SUCCESS;
}