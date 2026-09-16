#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} IntList;

bool sort_lists_by_index(IntList *lists, size_t count, size_t index)
{
    size_t i;

    if (count > 0U && lists == NULL) {
        return false;
    }

    for (i = 0U; i < count; ++i) {
        if (lists[i].data == NULL || index >= lists[i].length) {
            return false;
        }
    }

    for (i = 1U; i < count; ++i) {
        IntList current = lists[i];
        size_t position = i;

        while (position > 0U &&
               lists[position - 1U].data[index] > current.data[index]) {
            lists[position] = lists[position - 1U];
            --position;
        }

        lists[position] = current;
    }

    return true;
}

bool print_lists(const IntList *lists, size_t count)
{
    size_t i;
    size_t j;

    if (count > 0U && lists == NULL) {
        return false;
    }

    for (i = 0U; i < count; ++i) {
        if (lists[i].length > 0U && lists[i].data == NULL) {
            return false;
        }

        if (printf("[") < 0) {
            return false;
        }

        for (j = 0U; j < lists[i].length; ++j) {
            if (printf("%s%d", j == 0U ? "" : ", ", lists[i].data[j]) < 0) {
                return false;
            }
        }

        if (printf("]\n") < 0) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int first[] = {4, 8, 2};
    int second[] = {1, 3, 9};
    int third[] = {7, 5, 6};
    int fourth[] = {2, 1, 4};

    IntList lists[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])},
        {fourth, sizeof(fourth) / sizeof(fourth[0])}
    };

    const size_t count = sizeof(lists) / sizeof(lists[0]);
    const size_t sort_index = 1U;

    if (!sort_lists_by_index(lists, count, sort_index)) {
        if (fprintf(stderr, "Unable to sort the lists.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (!print_lists(lists, count)) {
        if (fprintf(stderr, "Unable to print the lists.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}