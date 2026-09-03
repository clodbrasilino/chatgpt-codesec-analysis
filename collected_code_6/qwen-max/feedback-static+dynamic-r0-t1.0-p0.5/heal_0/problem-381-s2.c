#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} List;

int compare(const void *a, const void *b, int index) {
    List *listA = (List *)a;
    List *listB = (List *)b;
    if (listA->data[index] < listB->data[index]) return -1;
    if (listA->data[index] > listB->data[index]) return 1;
    return 0;
}

void sort_lists(List *lists, size_t count, int index) {
    qsort(lists, count, sizeof(List), (int (*)(const void *, const void *))compare);
}

int main() {
    List lists[] = {
        { .data = (int[]){3, 2, 1}, .size = 3 },
        { .data = (int[]){1, 2, 3}, .size = 3 },
        { .data = (int[]){2, 3, 1}, .size = 3 }
    };
    size_t count = sizeof(lists) / sizeof(lists[0]);
    int index = 1;

    sort_lists(lists, count, index);

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = 0; j < lists[i].size; ++j) {
            printf("%d ", lists[i].data[j]);
        }
        printf("\n");
    }

    return 0;
}