#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int *elements;
    int length;
} Tuple;

int areAllTuplesEqualLength(Tuple *tuples, int tupleCount) {
    int length = tuples[0].length;
    for (int i = 1; i < tupleCount; i++) {
        if (tuples[i].length != length) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int tupleCount = 3;
    Tuple *tuples = malloc(sizeof(Tuple) * tupleCount);

    for (int i = 0; i < tupleCount; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'tuples' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        tuples[i].length = 5;
        tuples[i].elements = malloc(sizeof(int) * tuples[i].length);
    }

    printf("%s\n", areAllTuplesEqualLength(tuples, tupleCount) ? "All tuples are of equal length" : "All tuples are not of equal length");

    for (int i = 0; i < tupleCount; i++) {
        free(tuples[i].elements);
    }
    free(tuples);

    return 0;
}