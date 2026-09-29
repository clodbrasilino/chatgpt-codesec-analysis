#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *items;
    size_t length;
} IntList;

static int lists_are_equal(const IntList *left, const IntList *right)
{
    size_t i;

    if (left == NULL || right == NULL) {
        return 0;
    }

    if (left->length != right->length) {
        return 0;
    }

    if (left->length > 0U && (left->items == NULL || right->items == NULL)) {
        return 0;
    }

    for (i = 0U; i < left->length; ++i) {
        if (left->items[i] != right->items[i]) {
            return 0;
        }
    }

    return 1;
}

static int count_unique_lists(const IntList *lists, size_t count, size_t *result)
{
    size_t i;
    size_t j;
    size_t unique_count = 0U;

    if (result == NULL || (count > 0U && lists == NULL)) {
        return 0;
    }

    for (i = 0U; i < count; ++i) {
        int is_unique = 1;

        if (lists[i].length > 0U && lists[i].items == NULL) {
            return 0;
        }

        for (j = 0U; j < i; ++j) {
            if (lists_are_equal(&lists[i], &lists[j]) != 0) {
                is_unique = 0;
                break;
            }
        }

        if (is_unique != 0) {
            ++unique_count;
        }
    }

    *result = unique_count;
    return 1;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5};
    const int third[] = {1, 2, 3};
    const int fourth[] = {4, 5, 6};
    const IntList lists[] = {
        {first, sizeof first / sizeof first[0]},
        {second, sizeof second / sizeof second[0]},
        {third, sizeof third / sizeof third[0]},
        {fourth, sizeof fourth / sizeof fourth[0]},
        {NULL, 0U}
    };
    size_t unique_count = 0U;

    if (count_unique_lists(lists, sizeof lists / sizeof lists[0],
                           &unique_count) == 0) {
        (void)fprintf(stderr, "Failed to count unique lists.\n");
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", unique_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}