#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

Tuple* create_tuple(size_t size) {
    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    tuple->data = (int *)malloc(size * sizeof(int));
    tuple->length = 0;
    return tuple;
}

void free_tuple(Tuple *tuple) {
    free(tuple->data);
    free(tuple);
}

void trim_k(Tuple *tuple, int k) {
    if (k > 0 && k <= tuple->length) {
        memmove(tuple->data, tuple->data + k, (tuple->length - k) * sizeof(int));
        tuple->length -= k;
    }
}

int main() {
    Tuple *tuples[3];
    tuples[0] = create_tuple(10);
    tuples[1] = create_tuple(15);
    tuples[2] = create_tuple(8);

    tuples[0]->length = 7;
    tuples[1]->length = 12;
    tuples[2]->length = 4;

    int values0[] = {1, 2, 3, 4, 5, 6, 7};
    int values1[] = {8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    int values2[] = {20, 21, 22, 23};

    memcpy(tuples[0]->data, values0, tuples[0]->length * sizeof(int));
    memcpy(tuples[1]->data, values1, tuples[1]->length * sizeof(int));
    memcpy(tuples[2]->data, values2, tuples[2]->length * sizeof(int));

    int k = 2;

    for (size_t i = 0; i < 3; ++i) {
        trim_k(tuples[i], k);
        for (size_t j = 0; j < tuples[i]->length; ++j) {
            printf("%d ", tuples[i]->data[j]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < 3; ++i) {
        free_tuple(tuples[i]);
    }

    return 0;
}