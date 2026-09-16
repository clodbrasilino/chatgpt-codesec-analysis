#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    size_t length;
} IntList;

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static int compare_lists(const void *lhs, const void *rhs)
{
    const IntList *a = lhs;
    const IntList *b = rhs;
    size_t i;

    if (a->length != b->length) {
        return (a->length > b->length) - (a->length < b->length);
    }

    for (i = 0; i < a->length; ++i) {
        if (a->values[i] != b->values[i]) {
            return (a->values[i] > b->values[i]) -
                   (a->values[i] < b->values[i]);
        }
    }

    return 0;
}

static int sort_lists(IntList *lists, size_t count)
{
    size_t i;

    if (lists == NULL && count != 0U) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (lists[i].values == NULL && lists[i].length != 0U) {
            return -1;
        }

        if (lists[i].length > 1U) {
            qsort(lists[i].values, lists[i].length,
                  sizeof lists[i].values[0], compare_ints);
        }
    }

    if (count > 1U) {
        qsort(lists, count, sizeof lists[0], compare_lists);
    }

    return 0;
}

static int print_lists(const IntList *lists, size_t count)
{
    size_t i;
    size_t j;

    if (lists == NULL && count != 0U) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (lists[i].values == NULL && lists[i].length != 0U) {
            return -1;
        }

        if (putchar('[') == EOF) {
            return -1;
        }

        for (j = 0; j < lists[i].length; ++j) {
            if (printf("%s%d", j == 0U ? "" : ", ",
                       lists[i].values[j]) < 0) {
                return -1;
            }
        }

        if (puts("]") == EOF) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    int values0[] = {3, 1, 2};
    int values1[] = {5};
    int values2[] = {4, 2};
    int values3[] = {3, 2, 1};
    IntList lists[] = {
        {values0, sizeof values0 / sizeof values0[0]},
        {values1, sizeof values1 / sizeof values1[0]},
        {values2, sizeof values2 / sizeof values2[0]},
        {values3, sizeof values3 / sizeof values3[0]}
    };
    const size_t count = sizeof lists / sizeof lists[0];

    if (sort_lists(lists, count) != 0) {
        fputs("Failed to sort lists.\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_lists(lists, count) != 0) {
        fputs("Failed to print lists.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}