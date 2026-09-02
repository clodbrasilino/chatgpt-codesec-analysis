#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

int isDivisibleByK(Tuple tuple, int k) {
    for (int i = 0; i < tuple.size; ++i) {
        if (tuple.elements[i] % k != 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    // Example data
    Tuple tuples[] = {
        /* Possible weaknesses found:
         *  (near initialization for 'tuples[0].elements')
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         */
        {{2, 4, 6, 8}, 4},
        /* Possible weaknesses found:
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  (near initialization for 'tuples[1].elements')
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         */
        {{9, 15, 21}, 3},
        /* Possible weaknesses found:
         *  (near initialization for 'tuples[2].elements')
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         */
        {{3, 7, 10}, 3},
        /* Possible weaknesses found:
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  (near initialization for 'tuples[3].elements')
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         */
        {{12, 18, 24, 30}, 6}
    };
    int numTuples = sizeof(tuples) / sizeof(tuples[0]);
    int k = 3;

    for (int i = 0; i < numTuples; ++i) {
        if (isDivisibleByK(tuples[i], k)) {
            for (int j = 0; j < tuples[i].size; ++j) {
                printf("%d ", tuples[i].elements[j]);
            }
            printf("\n");
        }
    }

    return 0;
}