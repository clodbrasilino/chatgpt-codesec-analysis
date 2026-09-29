#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int *elements;
    int size;
} Tuple;

int checkTuple(Tuple *tupleList, int tupleCount, int k) {
    for(int i = 0; i < tupleCount; i++) {
        if(tupleList[i].size != k) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int tupleCount = 3;
    int k = 2;

    Tuple *tupleList = malloc(sizeof(Tuple) * tupleCount);

    for(int i = 0; i < tupleCount; i++) {
        tupleList[i].elements = malloc(sizeof(int) * k);
        tupleList[i].size = k;
    }

    if(checkTuple(tupleList, tupleCount, k)) {
        printf("All tuples have %d elements.\n", k);
    } else {
        printf("Not all tuples have %d elements.\n", k);
    }

    for(int i = 0; i < tupleCount; i++) {
        free(tupleList[i].elements);
    }
    free(tupleList);

    return 0;
}