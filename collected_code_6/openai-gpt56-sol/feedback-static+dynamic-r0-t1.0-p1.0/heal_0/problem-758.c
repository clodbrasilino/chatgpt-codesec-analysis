#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int *values;
    size_t length;
} List;

static bool lists_equal(const List *left, const List *right)
{
    size_t i;

    if (left == NULL || right == NULL) {
        return false;
    }

    if (left->length != right->length) {
        return false;
    }

    if (left->length > 0U && (left->values == NULL || right->values == NULL)) {
        return false;
    }

    for (i = 0U; i < left->length; ++i) {
        if (left->values[i] != right->values[i]) {
            return false;
        }
    }

    return true;
}

static bool count_unique_lists(const List *lists, size_t count, size_t *result)
{
    size_t unique_count = 0U;
    size_t i;
    size_t j;

    if (result == NULL || (count > 0U && lists == NULL)) {
        return false;
    }

    for (i = 0U; i < count; ++i) {
        bool is_unique = true;

        if (lists[i].length > 0U && lists[i].values == NULL) {
            return false;
        }

        for (j = 0U; j < i; ++j) {
            if (lists_equal(&lists[i], &lists[j])) {
                is_unique = false;
                break;
            }
        }

        if (is_unique) {
            ++unique_count;
        }
    }

    *result = unique_count;
    return true;
}

int main(void)
{
    int values1[] = {1, 2, 3};
    int values2[] = {4, 5};
    int values3[] = {1, 2, 3};
    int values4[] = {4, 5, 6};
    List lists[] = {
        {values1, sizeof(values1) / sizeof(values1[0])},
        {values2, sizeof(values2) / sizeof(values2[0])},
        {values3, sizeof(values3) / sizeof(values3[0])},
        {values4, sizeof(values4) / sizeof(values4[0])},
        {NULL, 0U}
    };
    size_t unique_count = 0U;
    const size_t list_count = sizeof(lists) / sizeof(lists[0]);

    if (!count_unique_lists(lists, list_count, &unique_count)) {
        fputs("Failed to count unique lists.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", unique_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}