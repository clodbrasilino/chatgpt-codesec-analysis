#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Tuple;

void trimTuple(Tuple *tuple, int k) {
    if (k >= tuple->size) {
        free(tuple->data);
        tuple->data = NULL;
        tuple->size = 0;
        return;
    }

    int *newData = (int *)malloc(sizeof(int) * (tuple->size - k));
    for (int i = 0; i < tuple->size - k; i++) {
        newData[i] = tuple->data[i];
    }

    free(tuple->data);
    tuple->data = newData;
    tuple->size -= k;
}

int main() {
    Tuple tuple;
    tuple.size = 5;
    tuple.data = (int *)malloc(sizeof(int) * tuple.size);
    for (int i = 0; i < tuple.size; i++) {
        tuple.data[i] = i + 1;
    }

    trimTuple(&tuple, 2);

    for (int i = 0; i < tuple.size; i++) {
        printf("%d ", tuple.data[i]);
    }

    free(tuple.data);

    return 0;
}