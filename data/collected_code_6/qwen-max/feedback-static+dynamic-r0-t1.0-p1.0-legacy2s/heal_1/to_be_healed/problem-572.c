#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int *array;
    size_t length;
} List;

void remove_duplicates(List list) {
    for (int i = 0; i < list.length; ++i) {
        for (int j = i + 1; j < list.length; ) {
            if (list.array[i] == list.array[j]) {
                for (size_t k = j; k < list.length - 1; ++k) {
                    list.array[k] = list.array[k + 1];
                }
                --list.length;
            } else {
                ++j;
            }
        }
    }
}

int main() {
    List lists[3] = {
        /* Possible weaknesses found:
         *  (near initialization for 'lists[0].array')
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         */
        {{1, 2, 3, 4, 4, 5, 6, 6, 7, 8}, 10},
        /* Possible weaknesses found:
         *  (near initialization for 'lists[1].array')
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         */
        {{9, 10, 10, 11, 12, 13, 14, 14, 15, 16, 16}, 11},
        /* Possible weaknesses found:
         *  (near initialization for 'lists[2].array')
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         */
        {{20, 21, 21, 22, 23, 24, 25, 26, 27, 28, 29, 20}, 12}
    };

    for (size_t i = 0; i < 3; ++i) {
        remove_duplicates(lists[i]);
        for (size_t j = 0; j < lists[i].length; ++j) {
            printf("%d ", lists[i].array[j]);
        }
        printf("\n");
    }

    return 0;
}