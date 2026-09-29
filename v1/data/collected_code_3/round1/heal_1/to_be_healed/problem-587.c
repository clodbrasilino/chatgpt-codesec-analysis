#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

Tuple* listToTuple(int* list, int size) {
    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'tuple' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    tuple->elements = (int*)malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*tuple.elements + (long unsigned int)i * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        tuple->elements[i] = list[i];
    }
    tuple->size = size;
    return tuple;
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    int size = sizeof(list) / sizeof(list[0]);
    Tuple* tuple = listToTuple(list, size);
    for(int i = 0; i < tuple->size; i++) {
        printf("%d ", tuple->elements[i]);
    }
    free(tuple->elements);
    free(tuple);
    return 0;
}