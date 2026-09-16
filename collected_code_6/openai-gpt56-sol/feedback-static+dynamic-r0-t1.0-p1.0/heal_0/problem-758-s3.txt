#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    const int *items;
    size_t length;
} IntList;

static bool lists_equal(const IntList *first, const IntList *second)
{
    size_t i;

    if (first->length != second->length) {
        return false;
    }

    if (first->length > 0 && (first->items == NULL || second->items == NULL)) {
        return false;
    }

    for (i = 0; i < first->length; ++i) {
        if (first->items[i] != second->items[i]) {
            return false;
        }
    }

    return true;
}

static bool count_unique_lists(const IntList *lists, size_t list_count,
                               size_t *unique_count)
{
    size_t count = 0;
    size_t i;

    if (unique_count == NULL || (list_count > 0 && lists == NULL)) {
        return false;
    }

    for (i = 0; i < list_count; ++i) {
        size_t j;
        bool unique = true;

        if (lists[i].length > 0 && lists[i].items == NULL) {
            return false;
        }

        for (j = 0; j < i; ++j) {
            if (lists_equal(&lists[i], &lists[j])) {
                unique = false;
                break;
            }
        }

        if (unique) {
            ++count;
        }
    }

    *unique_count = count;
    return true;
}

int main(void)
{
    const int values1[] = {1, 2, 3};
    const int values2[] = {4, 5};
    const int values3[] = {1, 2, 3};
    const int values4[] = {5, 4};
    const IntList lists[] = {
        {values1, sizeof values1 / sizeof values1[0]},
        {values2, sizeof values2 / sizeof values2[0]},
        {values3, sizeof values3 / sizeof values3[0]},
        {values4, sizeof values4 / sizeof values4[0]},
        {NULL, 0},
        {NULL, 0}
    };
    size_t unique_count;

    if (!count_unique_lists(lists, sizeof lists / sizeof lists[0],
                            &unique_count)) {
        fputs("Failed to count unique lists.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", unique_count);
    return EXIT_SUCCESS;
}