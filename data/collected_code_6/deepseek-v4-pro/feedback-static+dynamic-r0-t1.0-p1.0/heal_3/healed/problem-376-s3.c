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

    if (size * sizeof(int) <= (size_t)-1) {
        memcpy(tuple->data, values, size * sizeof(int));
    } else {
        free(tuple->data);
        tuple->data = NULL;
        return -1;
    }

    tuple->size = size;
    tuple->custom_value = custom_value;

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

    size_t *seen_indices = (size_t *)malloc(tuple->size * sizeof(size_t));
    if (seen_indices == NULL) {
        return -1;
    }

    size_t seen_count = 0;

    for (size_t i = 0; i < tuple->size; i++) {
        int found = 0;
        for (size_t s = 0; s < seen_count; s++) {
            if (tuple->data[i] == tuple->data[seen_indices[s]]) {
                found = 1;
                break;
            }
        }
        if (found) {
            tuple->data[i] = tuple->custom_value;
        } else {
            if (seen_count < tuple->size) {
                seen_indices[seen_count++] = i;
            }
        }
    }

    free(seen_indices);
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