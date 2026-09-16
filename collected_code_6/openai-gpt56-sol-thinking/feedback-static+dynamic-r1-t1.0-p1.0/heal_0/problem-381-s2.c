#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int *values;
    size_t length;
} IntList;

static void merge_lists(IntList *lists, IntList *temporary, size_t left,
                        size_t middle, size_t right, size_t index)
{
    size_t i = left;
    size_t j = middle;
    size_t k = left;

    while (i < middle && j < right) {
        if (lists[i].values[index] <= lists[j].values[index]) {
            temporary[k++] = lists[i++];
        } else {
            temporary[k++] = lists[j++];
        }
    }

    while (i < middle) {
        temporary[k++] = lists[i++];
    }

    while (j < right) {
        temporary[k++] = lists[j++];
    }

    for (k = left; k < right; ++k) {
        lists[k] = temporary[k];
    }
}

static void merge_sort_lists(IntList *lists, IntList *temporary, size_t left,
                             size_t right, size_t index)
{
    size_t middle;

    if (right - left < 2) {
        return;
    }

    middle = left + (right - left) / 2;
    merge_sort_lists(lists, temporary, left, middle, index);
    merge_sort_lists(lists, temporary, middle, right, index);
    merge_lists(lists, temporary, left, middle, right, index);
}

int sort_lists_by_index(IntList *lists, size_t count, size_t index)
{
    IntList *temporary;
    size_t i;

    if (count == 0) {
        return 0;
    }

    if (lists == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (lists[i].values == NULL || index >= lists[i].length) {
            return -1;
        }
    }

    if (count < 2) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*temporary)) {
        return -1;
    }

    temporary = malloc(count * sizeof(*temporary));
    if (temporary == NULL) {
        return -1;
    }

    merge_sort_lists(lists, temporary, 0, count, index);
    free(temporary);

    return 0;
}

static int print_lists(const IntList *lists, size_t count)
{
    size_t i;
    size_t j;

    for (i = 0; i < count; ++i) {
        if (putchar('[') == EOF) {
            return -1;
        }

        for (j = 0; j < lists[i].length; ++j) {
            if (j > 0 && fputs(", ", stdout) == EOF) {
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
    int first[] = {4, 8, 2};
    int second[] = {1, 3, 7};
    int third[] = {9, 5, 6};
    int fourth[] = {2, 1, 4};
    IntList lists[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])},
        {fourth, sizeof(fourth) / sizeof(fourth[0])}
    };
    const size_t count = sizeof(lists) / sizeof(lists[0]);
    const size_t index = 1;

    if (sort_lists_by_index(lists, count, index) != 0) {
        fputs("Unable to sort the lists.\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_lists(lists, count) != 0 || fflush(stdout) == EOF) {
        fputs("Unable to write the result.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}