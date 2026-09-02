#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} List;

int compare(const void *a, const void *b, int index) {
    const List *listA = (const List *)a;
    const List *listB = (const List *)b;
    return listA->data[index] - listB->data[index];
}

int compareWrapper(const void *a, const void *b) {
    static int index = 1; // Change this value as needed
    return compare(a, b, index);
}

void sortLists(List *lists, size_t count, int index) {
    qsort(lists, count, sizeof(List), (int (*)(const void *, const void *))compareWrapper);
}

int main() {
    List lists[] = {
        { (int[]){3, 2, 1}, 3 },
        { (int[]){6, 5, 4}, 3 },
        { (int[]){9, 8, 7}, 3 }
    };
    size_t count = sizeof(lists) / sizeof(lists[0]);

    sortLists(lists, count, 1);

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = 0; j < lists[i].size; ++j) {
            printf("%d ", lists[i].data[j]);
        }
        printf("\n");
    }

    return 0;
}