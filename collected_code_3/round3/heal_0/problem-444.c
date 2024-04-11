#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int *data;
    int size;
} Tuple;

Tuple* trimTuples(Tuple* tuples, int tupleCount, int k) {
    for(int i = 0; i < tupleCount; i++) {
        tuples[i].size -= k;
        tuples[i].data = realloc(tuples[i].data, tuples[i].size * sizeof(int));
    }
    return tuples;
}

int main() {
    int tupleCount = 3;
    int k = 2;
    Tuple* tuples = malloc(tupleCount * sizeof(Tuple));

    for(int i = 0; i < tupleCount; i++) {
        tuples[i].size = 5;
        tuples[i].data = malloc(tuples[i].size * sizeof(int));
        for(int j = 0; j < tuples[i].size; j++) {
            tuples[i].data[j] = j;
        }
    }

    tuples = trimTuples(tuples, tupleCount, k);

    for(int i = 0; i < tupleCount; i++) {
        for(int j = 0; j < tuples[i].size; j++) {
            printf("%d ", tuples[i].data[j]);
        }
        printf("\n");
    }

    for(int i = 0; i < tupleCount; i++) {
        free(tuples[i].data);
    }
    free(tuples);

    return 0;
}