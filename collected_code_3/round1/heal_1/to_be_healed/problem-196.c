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
    int j = 0;
    for (int i = 0; i < size; i++) {
        if (tuples[i].length != k) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'newTuples' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            newTuples[j++] = tuples[i];
        }
    }

    *newSize = count;
    return newTuples;
}

int main() {
    int size = 5;
    Tuple* tuples = (Tuple*)malloc(size * sizeof(Tuple));

    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'tuples' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        tuples[i].length = i + 1;
        tuples[i].elements = (int*)malloc(tuples[i].length * sizeof(int));
        for (int j = 0; j < tuples[i].length; j++) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*tuples_65 + _18.elements + (long unsigned int)j * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            tuples[i].elements[j] = j;
        }
    }

    int newSize;
    Tuple* newTuples = removeTuples(tuples, size, 3, &newSize);

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