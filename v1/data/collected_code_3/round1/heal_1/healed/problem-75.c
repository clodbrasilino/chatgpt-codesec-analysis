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
    Tuple *tuples = (Tuple *) malloc(sizeof(Tuple) * tupleCount);

    if(tuples == NULL){
        printf("Memory not allocated.\n");
        return 0;
    }

    for (int i = 0; i < tupleCount; i++) {
        tuples[i].size = 3;
        tuples[i].elements = (int *) malloc(sizeof(int) * tuples[i].size);

        if(tuples[i].elements == NULL){
            printf("Memory not allocated.\n");
            return 0;
        }

        for (int j = 0; j < tuples[i].size; j++) {
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