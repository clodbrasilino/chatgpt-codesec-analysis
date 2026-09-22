#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int *data;
    size_t length;
} Sublist;

int find_min_length_sublist(const Sublist *lists, size_t count, size_t *min_index)
{
    size_t i;
    size_t best;

    if (lists == NULL || min_index == NULL || count == 0U) {
        return -1;
    }

    best = 0U;
    for (i = 1U; i < count; i++) {
        if (lists[i].length < lists[best].length) {
            best = i;
        }
    }

    *min_index = best;
    return 0;
}

int main(void)
{
    int a[] = {1, 2, 3, 4};
    int b[] = {5, 6};
    int c[] = {7, 8, 9};
    Sublist lists[3];
    size_t min_index = 0U;
    size_t i;
    int result;

    lists[0].data = a;
    lists[0].length = sizeof(a) / sizeof(a[0]);
    lists[1].data = b;
    lists[1].length = sizeof(b) / sizeof(b[0]);
    lists[2].data = c;
    lists[2].length = sizeof(c) / sizeof(c[0]);

    result = find_min_length_sublist(lists, 3U, &min_index);
    if (result != 0) {
        (void)fprintf(stderr, "Error: invalid input to find_min_length_sublist\n");
        return EXIT_FAILURE;
    }

    if (printf("Minimum length sublist is at index %zu with length %zu: ",
               min_index, lists[min_index].length) < 0) {
        return EXIT_FAILURE;
    }

    for (i = 0U; i < lists[min_index].length; i++) {
        if (printf("%d ", lists[min_index].data[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (printf("\n") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}