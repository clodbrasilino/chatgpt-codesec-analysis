#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
} List;

List* createList(int size) {
    List *list = (List*)malloc(sizeof(List));
    list->size = size;
    list->elements = (int*)malloc(size * sizeof(int));
    return list;
}

void freeList(List *list) {
    free(list->elements);
    free(list);
}

List* findHighestSumList(List **lists, int numLists) {
    if (numLists == 0) return NULL;

    int maxSum = 0;
    List *maxList = NULL;

    for (int i = 0; i < numLists; ++i) {
        int currentSum = 0;
        for (int j = 0; j < lists[i]->size; ++j) {
            currentSum += lists[i]->elements[j];
        }
        if (i == 0 || currentSum > maxSum) {
            maxSum = currentSum;
            maxList = lists[i];
        }
    }

    return maxList;
}

int main() {
    List *list1 = createList(3);
    list1->elements[0] = 1;
    list1->elements[1] = 2;
    list1->elements[2] = 3;

    List *list2 = createList(3);
    list2->elements[0] = 4;
    list2->elements[1] = 5;
    list2->elements[2] = 6;

    List *list3 = createList(3);
    list3->elements[0] = 7;
    list3->elements[1] = 8;
    list3->elements[2] = 9;

    List *lists[] = {list1, list2, list3};
    int numLists = 3;

    List *maxList = findHighestSumList(lists, numLists);

    if (maxList != NULL) {
        printf("List with the highest sum: ");
        for (int i = 0; i < maxList->size; ++i) {
            printf("%d ", maxList->elements[i]);
        }
        printf("\n");
    } else {
        printf("No lists provided.\n");
    }

    freeList(list1);
    freeList(list2);
    freeList(list3);

    return 0;
}