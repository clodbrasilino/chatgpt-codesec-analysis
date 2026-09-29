#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

int tuple_init(Tuple *tuple, size_t size) {
    if (tuple == NULL || size == 0) {
        return -1;
    }
    
    tuple->data = malloc(size * sizeof(int));
    if (tuple->data == NULL) {
        return -1;
    }
    
    tuple->size = size;
    return 0;
}

int tuple_get(const Tuple *tuple, size_t index, int *value) {
    if (tuple == NULL || tuple->data == NULL || value == NULL) {
        return -1;
    }
    
    if (index >= tuple->size) {
        return -1;
    }
    
    *value = tuple->data[index];
    return 0;
}

void tuple_free(Tuple *tuple) {
    if (tuple != NULL && tuple->data != NULL) {
        free(tuple->data);
        tuple->data = NULL;
        tuple->size = 0;
    }
}

int main(void) {
    Tuple tuple;
    int value;
    size_t i;
    
    if (tuple_init(&tuple, 5) != 0) {
        fprintf(stderr, "Failed to initialize tuple\n");
        return EXIT_FAILURE;
    }
    
    for (i = 0; i < tuple.size; i++) {
        tuple.data[i] = (int)(i * 10);
    }
    
    if (tuple_get(&tuple, 2, &value) == 0) {
        printf("Value at index 2: %d\n", value);
    } else {
        fprintf(stderr, "Failed to get value\n");
    }
    
    tuple_free(&tuple);
    
    return EXIT_SUCCESS;
}