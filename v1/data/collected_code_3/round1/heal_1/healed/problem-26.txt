#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int *elements;
    int size;
} Tuple;

int checkElements(Tuple *tuples, int tupleSize, int k) {
    if (tuples == NULL) {
        return 0;
    }

    for(int i = 0; i < tupleSize; i++) {
        if(tuples[i].size != k) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int k = 3;
    int tupleSize = 2;
    Tuple *tuples = malloc(sizeof(Tuple) * tupleSize);

    if (tuples == NULL) {
        return -1;
    }

    for(int i = 0; i < tupleSize; i++) {
       
        tuples[i].elements = malloc(sizeof(int) * k);

        if (tuples[i].elements == NULL) {
            for (int j=0; j<i; ++j) {
                free(tuples[j].elements);
            }
            free(tuples);
            return -1;
        }

        tuples[i].size = k;
    }

    if(checkElements(tuples, tupleSize, k)) {
        printf("All tuples have %d elements.\n", k);
    } else {
        printf("Not all tuples have %d elements.\n", k);
    }

    for(int i = 0; i < tupleSize; i++) {
        free(tuples[i].elements);
    }
    free(tuples);

    return 0;
}