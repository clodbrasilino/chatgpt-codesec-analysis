#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} List;

List* findMaxSumList(List lists[], size_t n) {
    if (n == 0) return NULL;

    List *maxList = &lists[0];
    int maxSum = 0;

    for (size_t i = 0; i < n; ++i) {
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
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  (near initialization for 'lists[0].elements')
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         */
        {{1, 2, 3}, 3},
        /* Possible weaknesses found:
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  (near initialization for 'lists[1].elements')
         */
        {{4, 5, 6, 7}, 4},
        /* Possible weaknesses found:
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  (near initialization for 'lists[2].elements')
         */
        {{-1, -2, -3}, 3},
        /* Possible weaknesses found:
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  (near initialization for 'lists[3].elements')
         */
        {{8, 9}, 2}
    };
    size_t n = sizeof(lists) / sizeof(lists[0]);

    List *maxList = findMaxSumList(lists, n);

    if (maxList != NULL) {
        printf("Max Sum List: ");
        for (size_t i = 0; i < maxList->size; ++i) {
            printf("%d ", maxList->elements[i]);
        }
        printf("\n");
    } else {
        printf("No list found.\n");
    }

    return 0;
}