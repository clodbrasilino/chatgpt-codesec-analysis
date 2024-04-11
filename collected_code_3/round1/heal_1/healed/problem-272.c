#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple* createTuple(int a, int b) {
    Tuple* newTuple = (Tuple*)malloc(sizeof(Tuple));
    if (newTuple == NULL) {
        printf("Error allocating memory for tuple!\n");
        return NULL;
    }
    newTuple->a = a;
    newTuple->b = b;
    return newTuple;
}

int extractRear(Tuple** tuples, int size) {
    if (size == 0 || tuples == NULL) {
        printf("Error: list is empty or null\n");
        return -1;
    }
    if (tuples[size - 1] == NULL) {
        printf("Error: the last tuple is null\n");
        return -1;
    }
    return tuples[size - 1]->b;
}

int main() {
    int size = 5;
    Tuple** tuples = (Tuple**)malloc(size * sizeof(Tuple*));
    if (tuples == NULL) {
        printf("Error allocating memory for tuple array!\n");
        return -1;
    }
    for (int i = 0; i < size; i++) {
        tuples[i] = createTuple(i, i * 2);
        if (tuples[i] == NULL) {
            printf("Error allocating memory for tuple at index %d!\n", i);
        }
    }
    int rear = extractRear(tuples, size);
    if (rear != -1) {
        printf("Rear element: %d\n", rear);
    }
    for (int i = 0; i < size; i++) {
        free(tuples[i]);
    }
    free(tuples);
    return 0;
}