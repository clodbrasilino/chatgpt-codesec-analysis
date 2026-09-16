#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

Tuple* create_tuple(size_t length) {
    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->data = (int *)malloc(length * sizeof(int));
    if (tuple->data == NULL) {
        free(tuple);
        return NULL;
    }
    tuple->length = length;
    return tuple;
}

void delete_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        if (tuple->data != NULL) {
            free(tuple->data);
        }
        free(tuple);
    }
}

Tuple* get_colon_of_tuple(const Tuple *tuple, size_t start, size_t end) {
    if (start >= end || end > tuple->length) {
        return NULL;
    }
    Tuple *new_tuple = create_tuple(end - start);
    if (new_tuple == NULL) {
        return NULL;
    }
    for (size_t i = start; i < end; ++i) {
        new_tuple->data[i - start] = tuple->data[i];
    }
    return new_tuple;
}

int main() {
    Tuple *tuple = create_tuple(5);
    if (tuple == NULL) {
        return 1;
    }
    for (size_t i = 0; i < tuple->length; ++i) {
        tuple->data[i] = (int)i;
    }

    Tuple *colon_tuple = get_colon_of_tuple(tuple, 1, 4);
    if (colon_tuple == NULL) {
        delete_tuple(tuple);
        return 1;
    }

    for (size_t i = 0; i < colon_tuple->length; ++i) {
        printf("%d ", colon_tuple->data[i]);
    }
    printf("\n");

    delete_tuple(colon_tuple);
    delete_tuple(tuple);
    return 0;
}