#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple* createTuple(int a, int b) {
    Tuple* newTuple = (Tuple*)malloc(sizeof(Tuple));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newTuple' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newTuple->a = a;
    newTuple->b = b;
    return newTuple;
}

int extractRear(Tuple** tuples, int size) {
    if (size == 0) {
        printf("Error: list is empty\n");
        return -1;
    }
    return tuples[size - 1]->b;
}

int main() {
    int size = 5;
    Tuple** tuples = (Tuple**)malloc(size * sizeof(Tuple*));
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'tuples' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        tuples[i] = createTuple(i, i * 2);
    }
    int rear = extractRear(tuples, size);
    printf("Rear element: %d\n", rear);
    for (int i = 0; i < size; i++) {
        free(tuples[i]);
    }
    free(tuples);
    return 0;
}