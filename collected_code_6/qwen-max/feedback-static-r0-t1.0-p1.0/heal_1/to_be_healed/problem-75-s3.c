#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int size;
} Tuple;

int isDivisibleByK(int num, int k) {
    return num % k == 0;
}

int isTupleDivisibleByK(Tuple t, int k) {
    for (int i = 0; i < t.size; ++i) {
        if (!isDivisibleByK(t.arr[i], k)) {
            return 0;
        }
    }
    return 1;
}

void freeTuple(Tuple t) {
    free(t.arr);
}

int main() {
    Tuple tuples[] = {
        /* Possible weaknesses found:
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  (near initialization for 'tuples[0].arr')
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         */
        {{3, 6, 9}, 3},
        /* Possible weaknesses found:
         *  (near initialization for 'tuples[1].arr')
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         */
        {{2, 4, 8, 16}, 4},
        /* Possible weaknesses found:
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  (near initialization for 'tuples[2].arr')
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         */
        {{5, 10, 15, 20, 25}, 5},
        /* Possible weaknesses found:
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  (near initialization for 'tuples[3].arr')
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         */
        {{1, 2, 3, 4, 5}, 1}
    };
    int n = sizeof(tuples) / sizeof(tuples[0]);
    int k = 5;

    for (int i = 0; i < n; ++i) {
        if (isTupleDivisibleByK(tuples[i], k)) {
            for (int j = 0; j < tuples[i].size; ++j) {
                printf("%d ", tuples[i].arr[j]);
            }
            printf("\n");
        }
        freeTuple(tuples[i]);
    }

    return 0;
}