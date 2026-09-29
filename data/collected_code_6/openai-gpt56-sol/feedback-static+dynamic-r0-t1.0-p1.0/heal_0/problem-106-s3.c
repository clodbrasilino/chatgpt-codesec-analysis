#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int add_list_to_tuples(Tuple *tuples, size_t tuple_count,
                              const int *list, size_t list_count)
{
    size_t i;

    if ((tuple_count > 0 && tuples == NULL) ||
        (list_count > 0 && list == NULL) ||
        tuple_count != list_count) {
        return -1;
    }

    for (i = 0; i < tuple_count; ++i) {
        tuples[i].first += list[i];
        tuples[i].second += list[i];
    }

    return 0;
}

int main(void)
{
    Tuple tuples[] = {{1, 2}, {3, 4}, {5, 6}};
    const int list[] = {10, 20, 30};
    const size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    const size_t list_count = sizeof(list) / sizeof(list[0]);
    size_t i;

    if (add_list_to_tuples(tuples, tuple_count, list, list_count) != 0) {
        fputs("Failed to add list to tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < tuple_count; ++i) {
        if (printf("(%d, %d)\n", tuples[i].first, tuples[i].second) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}