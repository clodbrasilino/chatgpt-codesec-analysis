#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t count;
} Occurrence;

int count_occurrences(const int *tuple, size_t tuple_size,
                      const int *list, size_t list_size,
                      Occurrence *results)
{
    if ((tuple == NULL && tuple_size != 0) ||
        (list == NULL && list_size != 0) ||
        (results == NULL && list_size != 0)) {
        return -1;
    }

    for (size_t i = 0; i < list_size; ++i) {
        results[i].value = list[i];
        results[i].count = 0;

        for (size_t j = 0; j < tuple_size; ++j) {
            if (list[i] == tuple[j]) {
                ++results[i].count;
            }
        }
    }

    return 0;
}

int main(void)
{
    const int tuple[] = {1, 2, 3, 2, 4, 2, 1, 5};
    const int list[] = {1, 2, 4, 6};
    const size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    const size_t list_size = sizeof(list) / sizeof(list[0]);

    Occurrence *results = calloc(list_size, sizeof(*results));
    if (results == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (count_occurrences(tuple, tuple_size, list, list_size, results) != 0) {
        fputs("Invalid input\n", stderr);
        free(results);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < list_size; ++i) {
        if (printf("%d: %zu\n", results[i].value, results[i].count) < 0) {
            fputs("Output error\n", stderr);
            free(results);
            return EXIT_FAILURE;
        }
    }

    free(results);
    return EXIT_SUCCESS;
}