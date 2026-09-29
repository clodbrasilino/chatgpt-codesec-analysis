#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    const int *data;
    size_t length;
} IntList;

int find_max_length_list(const IntList *lists, size_t count, size_t *max_index)
{
    size_t i;
    size_t best;

    if (lists == NULL || max_index == NULL || count == 0U) {
        return -1;
    }

    best = 0U;
    for (i = 1U; i < count; i++) {
        if (lists[i].length > lists[best].length) {
            best = i;
        }
    }

    *max_index = best;
    return 0;
}

int main(void)
{
    const int list1[] = { 1, 2, 3 };
    const int list2[] = { 4, 5, 6, 7, 8 };
    const int list3[] = { 9, 10 };
    IntList lists[3];
    size_t max_index = 0U;
    size_t i;
    int result;

    lists[0].data = list1;
    lists[0].length = sizeof(list1) / sizeof(list1[0]);
    lists[1].data = list2;
    lists[1].length = sizeof(list2) / sizeof(list2[0]);
    lists[2].data = list3;
    lists[2].length = sizeof(list3) / sizeof(list3[0]);

    result = find_max_length_list(lists, sizeof(lists) / sizeof(lists[0]), &max_index);
    if (result != 0) {
        (void)fprintf(stderr, "Error: could not determine list with maximum length\n");
        return EXIT_FAILURE;
    }

    if (lists[max_index].data == NULL) {
        (void)fprintf(stderr, "Error: selected list has no data\n");
        return EXIT_FAILURE;
    }

    if (printf("List with maximum length (index %zu, length %zu): ",
               max_index, lists[max_index].length) < 0) {
        return EXIT_FAILURE;
    }

    for (i = 0U; i < lists[max_index].length; i++) {
        if (printf("%d ", lists[max_index].data[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (printf("\n") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}