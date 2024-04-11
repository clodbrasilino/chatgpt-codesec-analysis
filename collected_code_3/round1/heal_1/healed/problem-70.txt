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

    if (tuples == NULL) {
        printf("Failed to allocate memory for tuples.\n");
        return 1;
    }

    for (int i = 0; i < tupleCount; i++) {
        tuples[i].length = 5;
        tuples[i].elements = malloc(sizeof(int) * tuples[i].length);

        if (tuples[i].elements == NULL) {
            printf("Failed to allocate memory for tuple elements.\n");
            free(tuples);
            return 1;
        }
    }

    printf("%s\n", areAllTuplesEqualLength(tuples, tupleCount) ? "All tuples are of equal length" : "All tuples are not of equal length");

    for (int i = 0; i < tupleCount; i++) {
        free(tuples[i].elements);
    }
    free(tuples);

    return 0;
}