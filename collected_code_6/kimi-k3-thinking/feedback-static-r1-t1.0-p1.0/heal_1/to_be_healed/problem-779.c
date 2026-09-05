#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    const int *data;
    size_t length;
} IntList;

static bool lists_equal(const IntList *first, const IntList *second)
{
    size_t i;

    if (first == NULL || second == NULL) {
        return false;
    }
    if (first->length != second->length) {
        return false;
    }
    if (first->data == NULL || second->data == NULL) {
        return first->data == second->data;
    }
    for (i = 0; i < first->length; ++i) {
        if (first->data[i] != second->data[i]) {
            return false;
        }
    }
    return true;
}

size_t count_unique_lists(const IntList *lists, size_t list_count)
{
    size_t unique_count = 0;
    size_t i;
    size_t j;
    /* Possible weaknesses found:
     *  The scope of the variable 'duplicate' can be reduced. [variableScope]
     */
    bool duplicate;

    if (lists == NULL) {
        return 0;
    }

    for (i = 0; i < list_count; ++i) {
        duplicate = false;
        for (j = 0; j < i; ++j) {
            if (lists_equal(&lists[i], &lists[j])) {
                duplicate = true;
                break;
            }
        }
        if (!duplicate) {
            ++unique_count;
        }
    }

    return unique_count;
}

int main(void)
{
    const int values0[] = {1, 2, 3};
    const int values1[] = {4, 5};
    const int values2[] = {1, 2, 3};
    const int values3[] = {7};
    const int values4[] = {4, 5};
    const int values5[] = {1, 2};

    const IntList lists[] = {
        {values0, sizeof(values0) / sizeof(values0[0])},
        {values1, sizeof(values1) / sizeof(values1[0])},
        {values2, sizeof(values2) / sizeof(values2[0])},
        {values3, sizeof(values3) / sizeof(values3[0])},
        {values4, sizeof(values4) / sizeof(values4[0])},
        {values5, sizeof(values5) / sizeof(values5[0])}
    };

    const size_t list_count = sizeof(lists) / sizeof(lists[0]);
    const size_t unique_count = count_unique_lists(lists, list_count);

    if (printf("Number of unique lists: %zu\n", unique_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}