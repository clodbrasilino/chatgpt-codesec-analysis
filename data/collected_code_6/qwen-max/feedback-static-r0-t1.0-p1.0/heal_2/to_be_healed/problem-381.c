#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    int size;
} List;

int compare(const void *a, const void *b, int index) {
    List *listA = (List *)a;
    List *listB = (List *)b;
    return listA->items[index] - listB->items[index];
}

int compareWrapper(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Variable 'listA' can be declared as pointer to const [constVariablePointer]
     *  Variable 'listA' is assigned a value that is never used. [unreadVariable]
     */
    List *listA = (List *)a;
    /* Possible weaknesses found:
     *  Variable 'listB' can be declared as pointer to const [constVariablePointer]
     *  Variable 'listB' is assigned a value that is never used. [unreadVariable]
     */
    List *listB = (List *)b;
    int index = 1;  // or pass this as an argument if needed
    return compare(a, b, index);
}

void sortListOfLists(List *lists, int count, int index) {
    qsort(lists, count, sizeof(List), (int (*)(const void *, const void *))compareWrapper);
}

int main() {
    List lists[] = {
        /* Possible weaknesses found:
         *  (near initialization for 'lists[0].items')
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         */
        {{5, 2, 3}, 3},
        /* Possible weaknesses found:
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  (near initialization for 'lists[1].items')
         */
        {{4, 6, 1}, 3},
        /* Possible weaknesses found:
         *  (near initialization for 'lists[2].items')
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         */
        {{7, 8, 9}, 3}
    };
    int count = sizeof(lists) / sizeof(lists[0]);
    int index = 1;

    sortListOfLists(lists, count, index);

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < lists[i].size; j++) {
            printf("%d ", lists[i].items[j]);
        }
        printf("\n");
    }

    return 0;
}