#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

void trim_tuple(Tuple *t, int k) {
    if (k >= t->length) {
        free(t->data);
        t->data = NULL;
        t->length = 0;
        return;
    }
    t->length -= k;
    memmove(t->data, t->data + k, t->length * sizeof(int));
}

int main() {
    Tuple tuple = { .data = (int[]){1, 2, 3, 4, 5}, .length = 5 };
    int k = 2;

    trim_tuple(&tuple, k);

    for (size_t i = 0; i < tuple.length; ++i) {
        printf("%d ", tuple.data[i]);
    }

    free(tuple.data);
    return 0;
}