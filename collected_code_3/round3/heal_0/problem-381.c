#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *list;
    int size;
} List;

int compare(const void *a, const void *b) {
    List *listA = (List *)a;
    List *listB = (List *)b;
    return listA->list[0] - listB->list[0];
}

void sortListOfLists(List *lists, int size, int index) {
    for(int i = 0; i < size; i++) {
        qsort(lists[i].list, lists[i].size, sizeof(int), compare);
    }
}

int main() {
    int size = 3;
    List lists[3];

    int list1[] = {3, 2, 1};
    lists[0].list = list1;
    lists[0].size = sizeof(list1) / sizeof(int);

    int list2[] = {6, 5, 4};
    lists[1].list = list2;
    lists[1].size = sizeof(list2) / sizeof(int);

    int list3[] = {9, 8, 7};
    lists[2].list = list3;
    lists[2].size = sizeof(list3) / sizeof(int);

    sortListOfLists(lists, size, 0);

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < lists[i].size; j++) {
            printf("%d ", lists[i].list[j]);
        }
        printf("\n");
    }

    return 0;
}