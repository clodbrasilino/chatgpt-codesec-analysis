#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TUPLE_SIZE 10

typedef struct {
    int *data;
    size_t size;
    int custom_value;
} Tuple;

int init_tuple(Tuple *tuple, const int *values, size_t size, int custom_value) {
    if (tuple == NULL || values == NULL || size == 0) {
        return -1;
    }

    if (size > (size_t)-1 / sizeof(int)) {
        return -1;
    }

    tuple->data = (int *)malloc(size * sizeof(int));
    if (tuple->data == NULL) {
        return -1;
    }

    tuple->size = size;
    tuple->custom_value = custom_value;

    for (size_t i = 0; i < size; i++) {
        tuple->data[i] = values[i];
    }

    return 0;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL && tuple->data != NULL) {
        free(tuple->data);
        tuple->data = NULL;
        tuple->size = 0;
    }
}

int remove_duplicates(Tuple *tuple) {
    if (tuple == NULL || tuple->data == NULL || tuple->size == 0) {
        return -1;
    }

    size_t size = tuple->size;
    int *counts = (int *)calloc(size, sizeof(int));
    if (counts == NULL) {
        return -1;
    }

    for (size_t i = 0; i < size; i++) {
        if (counts[i] == 0) {
            counts[i] = 1;
            for (size_t j = i + 1; j < size; j++) {
                if (tuple->data[i] == tuple->data[j]) {
                    counts[i]++;
                    counts[j] = -1;
                }
            }
        }
    }

    for (size_t i = 0; i < size; i++) {
        if (counts[i] > 1 || counts[i] == -1) {
            tuple->data[i] = tuple->custom_value;
        }
    }

    free(counts);
    return 0;
}

int main(void) {
    const int values[TUPLE_SIZE] = {1, 2, 3, 2, 4, 5, 1, 6, 7, 3};
    Tuple tuple;

    if (init_tuple(&tuple, values, TUPLE_SIZE, -1) != 0) {
        return 1;
    }

    if (remove_duplicates(&tuple) != 0) {
        free_tuple(&tuple);
        return 1;
    }

    for (size_t i = 0; i < tuple.size; i++) {
        printf("%d ", tuple.data[i]);
    }
    printf("\n");

    free_tuple(&tuple);

    return 0;
}