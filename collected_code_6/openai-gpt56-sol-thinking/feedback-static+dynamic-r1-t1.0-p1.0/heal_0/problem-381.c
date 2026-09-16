#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    const int *values;
    size_t length;
} IntList;

typedef enum {
    SORT_SUCCESS,
    SORT_INVALID_ARGUMENT,
    SORT_INDEX_OUT_OF_RANGE
} SortResult;

SortResult sort_lists_by_index(IntList *lists, size_t count, size_t index)
{
    size_t i;

    if (lists == NULL && count != 0U) {
        return SORT_INVALID_ARGUMENT;
    }

    for (i = 0U; i < count; ++i) {
        if (lists[i].values == NULL || index >= lists[i].length) {
            return SORT_INDEX_OUT_OF_RANGE;
        }
    }

    for (i = 1U; i < count; ++i) {
        IntList current = lists[i];
        size_t position = i;

        while (position > 0U &&
               lists[position - 1U].values[index] > current.values[index]) {
            lists[position] = lists[position - 1U];
            --position;
        }

        lists[position] = current;
    }

    return SORT_SUCCESS;
}

int print_lists(const IntList *lists, size_t count)
{
    size_t i;

    if (lists == NULL && count != 0U) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        size_t j;

        if (lists[i].values == NULL && lists[i].length != 0U) {
            return -1;
        }

        if (fputc('[', stdout) == EOF) {
            return -1;
        }

        for (j = 0U; j < lists[i].length; ++j) {
            if (j != 0U && fputs(", ", stdout) == EOF) {
                return -1;
            }

            if (printf("%d", lists[i].values[j]) < 0) {
                return -1;
            }
        }

        if (fputs("]\n", stdout) == EOF) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    const int row1[] = {4, 9, 2};
    const int row2[] = {7, 3, 8};
    const int row3[] = {1, 6, 5};
    const int row4[] = {2, 1, 4};
    IntList lists[] = {
        {row1, sizeof(row1) / sizeof(row1[0])},
        {row2, sizeof(row2) / sizeof(row2[0])},
        {row3, sizeof(row3) / sizeof(row3[0])},
        {row4, sizeof(row4) / sizeof(row4[0])}
    };
    const size_t count = sizeof(lists) / sizeof(lists[0]);
    const size_t sort_index = 1U;
    SortResult result;

    result = sort_lists_by_index(lists, count, sort_index);
    if (result != SORT_SUCCESS) {
        if (fputs("Unable to sort the lists.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (print_lists(lists, count) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}