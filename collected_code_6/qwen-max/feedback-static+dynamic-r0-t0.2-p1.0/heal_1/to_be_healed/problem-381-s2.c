#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} List;

int compare(const void *a, const void *b, int index) {
    List *listA = (List *)a;
    List *listB = (List *)b;
    return listA->data[index] - listB->data[index];
}

void sortLists(List *lists, size_t count, int index) {
    qsort(lists, count, sizeof(List), (int (*)(const void *, const void *))compare);
}

int main() {
    List lists[] = {
        /* Possible weaknesses found:
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  (near initialization for 'lists[0].data')
         */
        {{3, 2, 1}, 3},
        /* Possible weaknesses found:
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  (near initialization for 'lists[1].data')
         */
        {{6, 5, 4}, 3},
        /* Possible weaknesses found:
         *  (near initialization for 'lists[2].data')
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         */
        {{9, 8, 7}, 3}
    };
    size_t count = sizeof(lists) / sizeof(lists[0]);

    sortLists(lists, count, 1);

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = 0; j < lists[i].size; ++j) {
            printf("%d ", lists[i].data[j]);
        }
        printf("\n");
    }

    return 0;
}