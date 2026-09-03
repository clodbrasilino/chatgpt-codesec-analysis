#include <stdio.h>
#include <stddef.h>
#include <limits.h>

int find_minimum_length_list(int **lists, const size_t *lengths, size_t count)
{
    if (lists == NULL || lengths == NULL || count == 0 || count > INT_MAX) {
        return -1;
    }

    size_t min_index = 0;

    if (lists[0] == NULL && lengths[0] > 0) {
        return -1;
    }

    for (size_t i = 1; i < count; ++i) {
        if (lists[i] == NULL && lengths[i] > 0) {
            return -1;
        }
        if (lengths[i] < lengths[min_index]) {
            min_index = i;
        }
    }

    return (int)min_index;
}

int main(void)
{
    int list0[] = {1, 2, 3};
    int list1[] = {4, 5};
    int list2[] = {6, 7, 8, 9};

    int *lists[] = {
        list0,
        list1,
        list2
    };

    size_t lengths[] = {
        sizeof(list0) / sizeof(list0[0]),
        sizeof(list1) / sizeof(list1[0]),
        sizeof(list2) / sizeof(list2[0])
    };

    int min_index = find_minimum_length_list(lists, lengths,
                                             sizeof(lengths) / sizeof(lengths[0]));

    if (min_index != -1) {
        for (size_t i = 0; i < lengths[min_index]; ++i) {
            printf("%d ", lists[min_index][i]);
        }
        printf("\n");
    }

    return 0;
}