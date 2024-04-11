#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tuple {
    int *elements;
    int length;
} Tuple;

Tuple* removeTuples(Tuple* tuples, int size, int k, int* newSize) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (tuples[i].length != k) {
            count++;
        }
    }

    Tuple* newTuples = (Tuple*)malloc(count * sizeof(Tuple));
    if (!newTuples) {
        return NULL;
    }

    int j = 0;
    for (int i = 0; i < size; i++) {
        if (tuples[i].length != k) {
            newTuples[j++] = tuples[i];
        }
    }

    *newSize = count;
    return newTuples;
}

int main() {
    int size = 5;
    Tuple* tuples = (Tuple*)malloc(size * sizeof(Tuple));
    if (!tuples) {
        return 1;
    }

    for (int i = 0; i < size; i++) {
        tuples[i].length = i + 1;
        tuples[i].elements = (int*)malloc(tuples[i].length * sizeof(int));
        if (!tuples[i].elements) {
            return 1;
        }
        for (int j = 0; j < tuples[i].length; j++) {
            tuples[i].elements[j] = j;
        }
    }

    int newSize;
    Tuple* newTuples = removeTuples(tuples, size, 3, &newSize);
    if (!newTuples) {
        return 1;
    }

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newTuples[i].length; j++) {
            printf("%d ", newTuples[i].elements[j]);
        }
        printf("\n");
    }

    for (int i = 0; i < size; i++) {
        free(tuples[i].elements);
    }
    free(tuples);

    for (int i = 0; i < newSize; i++) {
        free(newTuples[i].elements);
    }
    free(newTuples);

    return 0;
}