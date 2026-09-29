#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct {
    void **elements;
    size_t size;
    size_t capacity;
} Tuple;

Tuple* create_tuple(size_t count, ...) {
    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->elements = (void**)malloc(count * sizeof(void*));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }

    tuple->size = count;
    tuple->capacity = count;

    va_list args;
    va_start(args, count);
    for (size_t i = 0; i < count; i++) {
        tuple->elements[i] = va_arg(args, void*);
    }
    va_end(args);

    return tuple;
}

size_t get_tuple_size(const Tuple *tuple) {
    if (tuple == NULL) {
        return 0;
    }
    return tuple->size;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->elements);
        free(tuple);
    }
}

int main(void) {
    int a = 10;
    char b = 'x';
    double c = 3.14;

    Tuple *tuple = create_tuple(3, &a, &b, &c);
    if (tuple == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    size_t size = get_tuple_size(tuple);
    printf("Tuple size: %zu\n", size);

    free_tuple(tuple);
    return EXIT_SUCCESS;
}