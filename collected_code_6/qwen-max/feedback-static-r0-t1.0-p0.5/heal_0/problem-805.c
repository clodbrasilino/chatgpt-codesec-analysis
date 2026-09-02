#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} List;

List* findMaxSumList(List lists[], size_t numLists) {
    if (numLists == 0) return NULL;

    List *maxList = &lists[0];
    int maxSum = 0;

    for (size_t i = 0; i < numLists; ++i) {
        int sum = 0;
        for (size_t j = 0; j < lists[i].size; ++j) {
            sum += lists[i].elements[j];
        }
        if (sum > maxSum) {
            maxSum = sum;
            maxList = &lists[i];
        }
    }

    return maxList;
}

int main() {
    List lists[] = {
        { .elements = (int[]){1, 2, 3}, .size = 3 },
        { .elements = (int[]){4, 5, 6, 7}, .size = 4 },
        { .elements = (int[]){-1, -2, -3}, .size = 3 },
        { .elements = (int[]){8, 9}, .size = 2 }
    };

    size_t numLists = sizeof(lists) / sizeof(lists[0]);

    List *maxList = findMaxSumList(lists, numLists);

    if (maxList != NULL) {
        printf("Max sum list: ");
        for (size_t i = 0; i < maxList->size; ++i) {
            printf("%d ", maxList->elements[i]);
        }
        printf("\n");
    } else {
        printf("No lists provided.\n");
    }

    return 0;
}