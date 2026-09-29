#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int lists_equal(const int *first, size_t first_length,
                       const int *second, size_t second_length)
{
    size_t index;

    if (first_length != second_length) {
        return 0;
    }

    for (index = 0U; index < first_length; ++index) {
        if (first[index] != second[index]) {
            return 0;
        }
    }

    return 1;
}

static int count_unique_lists(const int *const *lists,
                              const size_t *lengths,
                              size_t list_count,
                              size_t *unique_count)
{
    size_t current;
    size_t previous;
    size_t count = 0U;

    if (unique_count == NULL) {
        return -1;
    }

    *unique_count = 0U;

    if (list_count > 0U && (lists == NULL || lengths == NULL)) {
        return -1;
    }

    for (current = 0U; current < list_count; ++current) {
        int is_unique = 1;

        if (lengths[current] > 0U && lists[current] == NULL) {
            return -1;
        }

        for (previous = 0U; previous < current; ++previous) {
            if (lists_equal(lists[current], lengths[current],
                            lists[previous], lengths[previous]) != 0) {
                is_unique = 0;
                break;
            }
        }

        if (is_unique != 0) {
            ++count;
        }
    }

    *unique_count = count;
    return 0;
}

int main(void)
{
    const int list1[] = {1, 2, 3};
    const int list2[] = {4, 5};
    const int list3[] = {1, 2, 3};
    const int list4[] = {6};
    const int list5[] = {4, 5};
    const int *const lists[] = {list1, list2, list3, list4, list5};
    const size_t lengths[] = {
        sizeof(list1) / sizeof(list1[0]),
        sizeof(list2) / sizeof(list2[0]),
        sizeof(list3) / sizeof(list3[0]),
        sizeof(list4) / sizeof(list4[0]),
        sizeof(list5) / sizeof(list5[0])
    };
    const size_t list_count = sizeof(lists) / sizeof(lists[0]);
    size_t unique_count;

    if (count_unique_lists(lists, lengths, list_count, &unique_count) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", unique_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}