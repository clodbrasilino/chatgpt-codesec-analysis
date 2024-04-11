#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int *elements;
    int size;
} Tuple;

Tuple* trimTuple(Tuple *tuple, int k) {
    if (k >= tuple->size) {
        return NULL;
    }

    Tuple *trimmedTuple = (Tuple*) malloc(sizeof(Tuple));
    trimmedTuple->size = tuple->size - k;
    trimmedTuple->elements = (int*) malloc(trimmedTuple->size * sizeof(int));

    for (int i = 0; i < trimmedTuple->size; i++) {
        trimmedTuple->elements[i] = tuple->elements[i];
    }

    return trimmedTuple;
}

int main() {
    int size = 5;
    int k = 2;
    Tuple tuple;
    tuple.size = size;
    tuple.elements = (int*) malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        tuple.elements[i] = i + 1;
    }

    Tuple *trimmedTuple = trimTuple(&tuple, k);

    if (trimmedTuple != NULL) {
        for (int i = 0; i < trimmedTuple->size; i++) {
            printf("%d ", trimmedTuple->elements[i]);
        }
        free(trimmedTuple->elements);
        free(trimmedTuple);
    } else {
        printf("Trimmed size is greater than tuple size.\n");
    }

    free(tuple.elements);

    return 0;
}