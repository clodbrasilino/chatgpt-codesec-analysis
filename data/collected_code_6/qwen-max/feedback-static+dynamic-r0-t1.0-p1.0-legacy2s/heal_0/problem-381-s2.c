#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} List;

int compare(const void *a, const void *b, size_t index) {
    List *listA = (List *)a;
    List *listB = (List *)b;
    if (index >= listA->size || index >= listB->size) {
        return 0;
    }
    return (listA->data[index] - listB->data[index]);
}

int customCompare(const void *a, const void *b) {
    return compare(a, b, 2); // Sort by the 2nd element (index 1)
}

void printList(List *list) {
    for (size_t i = 0; i < list->size; ++i) {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

int main() {
    size_t numLists = 3;
    List lists[] = {
        { .data = (int[]){5, 3, 7}, .size = 3 },
        { .data = (int[]){1, 9, 2}, .size = 3 },
        { .data = (int[]){8, 4, 6}, .size = 3 }
    };

    qsort(lists, numLists, sizeof(List), customCompare);

    for (size_t i = 0; i < numLists; ++i) {
        printList(&lists[i]);
    }

    return 0;
}