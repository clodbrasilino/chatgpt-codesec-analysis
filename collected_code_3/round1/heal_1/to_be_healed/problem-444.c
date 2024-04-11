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
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'trimmedTuple' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    trimmedTuple->size = tuple->size - k;
    trimmedTuple->elements = (int*) malloc(trimmedTuple->size * sizeof(int));

    for (int i = 0; i < trimmedTuple->size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*trimmedTuple.elements + (long unsigned int)i * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
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
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'tuple.elements' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
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