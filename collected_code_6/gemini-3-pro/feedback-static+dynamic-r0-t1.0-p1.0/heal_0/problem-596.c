#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void **elements;
    size_t size;
} Tuple;

Tuple* create_tuple(size_t size) {
    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }
    
    tuple->elements = (void**)malloc(size * sizeof(void*));
    if (!tuple->elements) {
        free(tuple);
        return NULL;
    }
    
    tuple->size = size;
    return tuple;
}

void destroy_tuple(Tuple *tuple) {
    if (tuple) {
        free(tuple->elements);
        free(tuple);
    }
}

size_t get_tuple_size(const Tuple *tuple) {
    if (!tuple) {
        return 0;
    }
    return tuple->size;
}

int main(void) {
    Tuple *tuple = create_tuple(5);
    if (!tuple) {
        return EXIT_FAILURE;
    }
    
    size_t size = get_tuple_size(tuple);
    printf("%zu\n", size);
    
    destroy_tuple(tuple);
    return EXIT_SUCCESS;
}