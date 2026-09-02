#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} Sublist;

Sublist* findMaxSublist(Sublist *lists, size_t numLists) {
    if (numLists == 0) return NULL;
    Sublist *maxList = lists;
    for (size_t i = 1; i < numLists; i++) {
        if (lists[i].length > maxList->length) {
            maxList = &lists[i];
        }
    }
    return maxList;
}

int main() {
    Sublist lists[] = {
        /* Possible weaknesses found:
         *  (near initialization for 'lists[0].data')
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         */
        {{1, 2, 3}, 3},
        /* Possible weaknesses found:
         *  (near initialization for 'lists[1].data')
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         */
        {{4, 5}, 2},
        /* Possible weaknesses found:
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  (near initialization for 'lists[2].data')
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         */
        {{6, 7, 8, 9}, 4}
    };
    size_t numLists = sizeof(lists) / sizeof(lists[0]);

    Sublist *maxSublist = findMaxSublist(lists, numLists);
    if (maxSublist != NULL) {
        for (size_t i = 0; i < maxSublist->length; i++) {
            printf("%d ", maxSublist->data[i]);
        }
        printf("\n");
    } else {
        printf("No sublists provided.\n");
    }

    return 0;
}