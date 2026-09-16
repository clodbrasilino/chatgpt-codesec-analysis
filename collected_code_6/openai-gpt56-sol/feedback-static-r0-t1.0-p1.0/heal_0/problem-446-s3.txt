#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t count;
} ElementCount;

int count_occurrences(const int *list, size_t list_size,
                      const int *tuple, size_t tuple_size,
                      ElementCount *results)
{
    if ((list_size > 0 && list == NULL) ||
        (tuple_size > 0 && tuple == NULL) ||
        (list_size > 0 && results == NULL)) {
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
    const int list[] = {1, 2, 3, 4, 5};
    const int tuple[] = {1, 2, 2, 3, 3, 3, 5, 5};
    const size_t list_size = sizeof list / sizeof list[0];
    const size_t tuple_size = sizeof tuple / sizeof tuple[0];

    ElementCount *results = calloc(list_size, sizeof *results);
    if (results == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (count_occurrences(list, list_size, tuple, tuple_size, results) != 0) {
        fputs("Invalid function arguments\n", stderr);
        free(results);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < list_size; ++i) {
        printf("%d: %zu\n", results[i].value, results[i].count);
    }

    free(results);
    return EXIT_SUCCESS;
}