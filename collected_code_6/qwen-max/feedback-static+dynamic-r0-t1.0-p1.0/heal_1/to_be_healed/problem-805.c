#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t count;
} IntList;

IntList* findMaxSumList(IntList *lists, size_t n) {
    if (n == 0) return NULL;
    IntList *maxList = lists;
    int maxSum = 0;
    for (size_t i = 0; i < n; ++i) {
        int sum = 0;
        for (size_t j = 0; j < lists[i].count; ++j) {
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
    IntList lists[] = {
        /* Possible weaknesses found:
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  (near initialization for 'lists[0].elements')
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         */
        {{1, 2, 3}, 3},
        /* Possible weaknesses found:
         *  (near initialization for 'lists[1].elements')
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         */
        {{4, 5, 6, 7}, 4},
        /* Possible weaknesses found:
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  (near initialization for 'lists[2].elements')
         */
        {{8, 9}, 2},
        /* Possible weaknesses found:
         *  (near initialization for 'lists[3].elements')
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         */
        {{-1, -2, -3}, 3}
    };
    size_t n = sizeof(lists) / sizeof(lists[0]);
    
    IntList *maxList = findMaxSumList(lists, n);
    
    printf("Max Sum List: [");
    for (size_t i = 0; i < maxList->count; ++i) {
        printf("%d%s", maxList->elements[i], i < maxList->count - 1 ? ", " : "");
    }
    printf("]\n");
    
    return 0;
}