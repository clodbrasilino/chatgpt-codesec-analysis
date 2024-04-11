#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int *elements;
    int size;
} Tuple;

int isDivisible(Tuple tuple, int k) {
    for (int i = 0; i < tuple.size; i++) {
        if (tuple.elements[i] % k != 0) {
            return 0;
        }
    }
    return 1;
}

void findDivisibleTuples(Tuple *tuples, int tupleCount, int k) {
    for (int i = 0; i < tupleCount; i++) {
        if (isDivisible(tuples[i], k)) {
            printf("Tuple %d is divisible by %d\n", i, k);
        }
    }
}

int main() {
    int tupleCount = 3;
    Tuple *tuples = malloc(sizeof(Tuple) * tupleCount);

    for (int i = 0; i < tupleCount; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'tuples' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        tuples[i].size = 3;
        tuples[i].elements = malloc(sizeof(int) * tuples[i].size);
        for (int j = 0; j < tuples[i].size; j++) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*tuples_43 + _19.elements + (long unsigned int)j * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            tuples[i].elements[j] = (i + 1) * (j + 1);
        }
    }

    findDivisibleTuples(tuples, tupleCount, 2);

    for (int i = 0; i < tupleCount; i++) {
        free(tuples[i].elements);
    }
    free(tuples);

    return 0;
}