#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int *values;
    size_t length;
} IntList;

static int compare_ints(const void *lhs, const void *rhs)
{
    const int left = *(const int *)lhs;
    const int right = *(const int *)rhs;

    return (left > right) - (left < right);
}

static int compare_lists(const void *lhs, const void *rhs)
{
    const IntList *left = lhs;
    const IntList *right = rhs;
    size_t limit;
    size_t index;

    if (left->length != right->length) {
        return (left->length > right->length) - (left->length < right->length);
    }

    limit = left->length;
    for (index = 0; index < limit; ++index) {
        if (left->values[index] != right->values[index]) {
            return (left->values[index] > right->values[index]) -
                   (left->values[index] < right->values[index]);
        }
    }

    return 0;
}

static void sort_lists(IntList *lists, size_t count)
{
    size_t index;

    if (lists == NULL && count != 0U) {
        return;
    }

    for (index = 0; index < count; ++index) {
        if (lists[index].values != NULL && lists[index].length > 1U) {
            qsort(lists[index].values, lists[index].length,
                  sizeof(*lists[index].values), compare_ints);
        }
    }

    if (count > 1U) {
        qsort(lists, count, sizeof(*lists), compare_lists);
    }
}

static void free_lists(IntList *lists, size_t count)
{
    size_t index;

    if (lists == NULL) {
        return;
    }

    for (index = 0; index < count; ++index) {
        free(lists[index].values);
    }

    free(lists);
}

int main(void)
{
    IntList *lists = NULL;
    size_t count;
    size_t index;
    size_t value_index;

    if (scanf("%zu", &count) != 1) {
        fputs("Failed to read the number of lists.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0U) {
        lists = calloc(count, sizeof(*lists));
        if (lists == NULL) {
            fputs("Failed to allocate list storage.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (index = 0; index < count; ++index) {
        if (scanf("%zu", &lists[index].length) != 1) {
            fputs("Failed to read a list length.\n", stderr);
            free_lists(lists, count);
            return EXIT_FAILURE;
        }

        if (lists[index].length > SIZE_MAX / sizeof(*lists[index].values)) {
            fputs("List size is too large.\n", stderr);
            free_lists(lists, count);
            return EXIT_FAILURE;
        }

        if (lists[index].length != 0U) {
            lists[index].values =
                malloc(lists[index].length * sizeof(*lists[index].values));
            if (lists[index].values == NULL) {
                fputs("Failed to allocate list values.\n", stderr);
                free_lists(lists, count);
                return EXIT_FAILURE;
            }
        }

        for (value_index = 0; value_index < lists[index].length; ++value_index) {
            if (scanf("%d", &lists[index].values[value_index]) != 1) {
                fputs("Failed to read a list value.\n", stderr);
                free_lists(lists, count);
                return EXIT_FAILURE;
            }
        }
    }

    sort_lists(lists, count);

    for (index = 0; index < count; ++index) {
        printf("%zu", lists[index].length);
        for (value_index = 0; value_index < lists[index].length; ++value_index) {
            printf(" %d", lists[index].values[value_index]);
        }
        putchar('\n');
    }

    free_lists(lists, count);
    return EXIT_SUCCESS;
}