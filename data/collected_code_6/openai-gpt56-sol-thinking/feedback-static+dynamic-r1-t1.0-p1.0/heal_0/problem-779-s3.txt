#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *values;
    size_t length;
} IntList;

static bool lists_equal(const IntList *left, const IntList *right)
{
    size_t i;

    if (left->length != right->length) {
        return false;
    }

    for (i = 0; i < left->length; ++i) {
        if (left->values[i] != right->values[i]) {
            return false;
        }
    }

    return true;
}

static bool count_unique_lists(const IntList *lists, size_t list_count,
                               size_t *unique_count)
{
    size_t i;
    size_t j;
    size_t count = 0;

    if (unique_count == NULL || (list_count != 0 && lists == NULL)) {
        return false;
    }

    *unique_count = 0;

    for (i = 0; i < list_count; ++i) {
        bool unique = true;

        if (lists[i].length != 0 && lists[i].values == NULL) {
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
    static const int first[] = {1, 2, 3};
    static const int second[] = {4, 5};
    static const int third[] = {1, 2, 3};
    static const int fourth[] = {6};
    static const IntList lists[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])},
        {fourth, sizeof(fourth) / sizeof(fourth[0])},
        {NULL, 0},
        {NULL, 0}
    };
    size_t unique_count;

    if (!count_unique_lists(lists, sizeof(lists) / sizeof(lists[0]),
                            &unique_count)) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", unique_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}