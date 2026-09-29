#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    size_t length;
} IntList;

int compare_lists(const void *a, const void *b) {
    const IntList *list_a = (const IntList *)a;
    const IntList *list_b = (const IntList *)b;

    if (list_a->length != list_b->length) {
        return (list_a->length < list_b->length) ? -1 : 1;
    }

    for (size_t i = 0; i < list_a->length; ++i) {
        if (list_a->values[i] != list_b->values[i]) {
            return (list_a->values[i] < list_b->values[i]) ? -1 : 1;
        }
    }

    return 0;
}

void sort_list_of_lists(IntList *lists, size_t num_lists) {
    if (!lists || num_lists == 0) {
        return;
    }
    qsort(lists, num_lists, sizeof(IntList), compare_lists);
}

int main(void) {
    IntList lists[4];
    
    int vals0[] = {1, 2, 3};
    lists[0].values = vals0;
    lists[0].length = 3;

    int vals1[] = {1, 2};
    lists[1].values = vals1;
    lists[1].length = 2;

    int vals2[] = {1, 2, 4};
    lists[2].values = vals2;
    lists[2].length = 3;

    int vals3[] = {5};
    lists[3].values = vals3;
    lists[3].length = 1;

    size_t num_lists = sizeof(lists) / sizeof(lists[0]);

    sort_list_of_lists(lists, num_lists);

    for (size_t i = 0; i < num_lists; ++i) {
        printf("[");
        for (size_t j = 0; j < lists[i].length; ++j) {
            printf("%d", lists[i].values[j]);
            if (j < lists[i].length - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }

    return 0;
}