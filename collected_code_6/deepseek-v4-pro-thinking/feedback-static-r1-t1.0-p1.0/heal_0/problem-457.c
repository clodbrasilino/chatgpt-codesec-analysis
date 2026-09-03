#include <stdio.h>

typedef struct {
    int *data;
    int length;
} Sublist;

int find_minimum_length_sublist(const Sublist *sublists, int count, int *min_index) {
    if (sublists == NULL || count <= 0 || min_index == NULL) {
        return -1;
    }

    int min_length = -1;
    int best_index = -1;

    for (int i = 0; i < count; ++i) {
        if (sublists[i].length < 0) {
            return -1;
        }
        if (sublists[i].length > 0 && sublists[i].data == NULL) {
            return -1;
        }
        if (best_index == -1 || sublists[i].length < min_length) {
            min_length = sublists[i].length;
            best_index = i;
        }
    }

    if (best_index == -1) {
        return -1;
    }

    *min_index = best_index;
    return min_length;
}

int main(void) {
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5};
    int list3[] = {6, 7, 8, 9};

    Sublist sublists[] = {
        {list1, 3},
        {list2, 2},
        {list3, 4}
    };

    int count = (int)(sizeof(sublists) / sizeof(sublists[0]));
    int min_index = -1;
    int min_length = find_minimum_length_sublist(sublists, count, &min_index);

    if (min_length >= 0 && min_index >= 0) {
        printf("Minimum length: %d\n", min_length);
        printf("Sublist: ");
        for (int i = 0; i < sublists[min_index].length; ++i) {
            printf("%d", sublists[min_index].data[i]);
            if (i < sublists[min_index].length - 1) {
                printf(" ");
            }
        }
        printf("\n");
    } else {
        printf("No valid sublist found\n");
    }

    return 0;
}