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
    List lists[] = {
        /* Possible weaknesses found:
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  (near initialization for 'lists[0].elements')
         */
        {{1, 2, 3}, 3},
        /* Possible weaknesses found:
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  (near initialization for 'lists[1].elements')
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         */
        {{4, 5, 6}, 3},
        /* Possible weaknesses found:
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  (near initialization for 'lists[2].elements')
         */
        {{-1, -2, -3}, 3},
        /* Possible weaknesses found:
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  (near initialization for 'lists[3].elements')
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         */
        {{7, 8, 9}, 3}
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