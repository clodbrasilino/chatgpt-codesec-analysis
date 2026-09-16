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

static int count_unique_lists(const IntList *lists, size_t list_count,
                              size_t *unique_count)
{
    size_t i;
    size_t j;

    if (unique_count == NULL) {
        return -1;
    }

    *unique_count = 0;

    if (list_count != 0 && lists == NULL) {
        return -1;
    }

    for (i = 0; i < list_count; ++i) {
        bool unique = true;

        if (lists[i].length != 0 && lists[i].values == NULL) {
            return -1;
        }

        for (j = 0; j < i; ++j) {
            if (lists_equal(&lists[i], &lists[j])) {
                unique = false;
                break;
            }
        }

        if (unique) {
            ++*unique_count;
        }
    }

    return 0;
}

int main(void)
{
    static const int values1[] = {1, 2, 3};
    static const int values2[] = {4, 5};
    static const int values3[] = {1, 2, 3};
    static const int values4[] = {5, 4};
    static const IntList lists[] = {
        {values1, sizeof(values1) / sizeof(values1[0])},
        {values2, sizeof(values2) / sizeof(values2[0])},
        {values3, sizeof(values3) / sizeof(values3[0])},
        {values4, sizeof(values4) / sizeof(values4[0])},
        {NULL, 0},
        {NULL, 0}
    };
    size_t unique_count;

    if (count_unique_lists(lists, sizeof(lists) / sizeof(lists[0]),
                           &unique_count) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", unique_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}