#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int* data;
    size_t size;
} Tuple;

Tuple* create_tuple(size_t size) {
    if (size == 0) {
        return NULL;
    }
    
    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    
    tuple->data = (int*)malloc(size * sizeof(int));
    if (tuple->data == NULL) {
        free(tuple);
        return NULL;
    }
    
    tuple->size = size;
    return tuple;
}

void destroy_tuple(Tuple* tuple) {
    if (tuple != NULL) {
        free(tuple->data);
        free(tuple);
    }
}

int get_initial_and_last_data(const Tuple* tuple, int* initial, int* last) {
    if (tuple == NULL || tuple->data == NULL || tuple->size == 0 || initial == NULL || last == NULL) {
        return -1;
    }
    
    *initial = tuple->data[0];
    *last = tuple->data[tuple->size - 1];
    
    return 0;
}

int main(void) {
    size_t tuple_size = 5;
    Tuple* tuple = create_tuple(tuple_size);
    if (tuple == NULL) {
        return 1;
    }
    
    for (size_t i = 0; i < tuple_size; ++i) {
        tuple->data[i] = (int)(i + 1) * 10;
    }
    
    int initial_val = 0;
    int last_val = 0;
    
    if (get_initial_and_last_data(tuple, &initial_val, &last_val) == 0) {
        printf("Initial: %d\n", initial_val);
        printf("Last: %d\n", last_val);
    }
    
    destroy_tuple(tuple);
    
    return 0;
}