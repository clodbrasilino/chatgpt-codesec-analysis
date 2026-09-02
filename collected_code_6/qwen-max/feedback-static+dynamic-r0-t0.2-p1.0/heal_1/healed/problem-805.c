#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} List;

List* findMaxSumList(List lists[], size_t numLists) {
    if (numLists == 0) return NULL;

    List* maxList = &lists[0];
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
    int elements1[] = {1, 2, 3};
    int elements2[] = {4, 5, 6};
    int elements3[] = {-1, -2, -3};
    int elements4[] = {7, 8, 9};

    List lists[] = {
        {elements1, 3},
        {elements2, 3},
        {elements3, 3},
        {elements4, 3}
    };

    size_t numLists = sizeof(lists) / sizeof(lists[0]);

    List* maxList = findMaxSumList(lists, numLists);

    if (maxList != NULL) {
        printf("List with the highest sum: ");
        for (size_t i = 0; i < maxList->size; ++i) {
            printf("%d ", maxList->elements[i]);
        }
        printf("\n");
    } else {
        printf("No lists provided.\n");
    }

    return 0;
}