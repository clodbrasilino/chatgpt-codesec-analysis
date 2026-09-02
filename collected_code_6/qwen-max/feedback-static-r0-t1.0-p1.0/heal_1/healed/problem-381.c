#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    int size;
} List;

int compare(const void *a, const void *b, int index) {
    List *listA = (List *)a;
    List *listB = (List *)b;
    return listA->items[index] - listB->items[index];
}

int compareWrapper(const void *a, const void *b) {
    List *listA = (List *)a;
    List *listB = (List *)b;
    int index = 1;  // or pass this as an argument if needed
    return compare(a, b, index);
}

void sortListOfLists(List *lists, int count, int index) {
    qsort(lists, count, sizeof(List), (int (*)(const void *, const void *))compareWrapper);
}

int main() {
    List lists[] = {
        {{5, 2, 3}, 3},
        {{4, 6, 1}, 3},
        {{7, 8, 9}, 3}
    };
    int count = sizeof(lists) / sizeof(lists[0]);
    int index = 1;

    sortListOfLists(lists, count, index);

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < lists[i].size; j++) {
            printf("%d ", lists[i].items[j]);
        }
        printf("\n");
    }

    return 0;
}