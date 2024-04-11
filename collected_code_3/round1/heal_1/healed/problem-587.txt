#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

Tuple* listToTuple(int* list, int size) {
    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->elements = (int*)malloc(sizeof(int) * size);
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }

    for(int i = 0; i < size; i++) {
        tuple->elements[i] = list[i];
    }
    tuple->size = size;
    return tuple;
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    int size = sizeof(list) / sizeof(list[0]);
    Tuple* tuple = listToTuple(list, size);

    if (tuple == NULL) {
        return 1;
    }

    for(int i = 0; i < tuple->size; i++) {
        printf("%d ", tuple->elements[i]);
    }

    free(tuple->elements);
    free(tuple);
    return 0;
}