#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef struct {
    void **elements;
    size_t count;
} Tuple;

Tuple* tuple_create(size_t count, ...) {
    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    
    tuple->elements = (void**)calloc(count, sizeof(void*));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }
    
    tuple->count = count;
    
    va_list args;
    va_start(args, count);
    
    for (size_t i = 0; i < count; i++) {
        tuple->elements[i] = va_arg(args, void*);
    }
    
    va_end(args);
    
    return tuple;
}

void tuple_destroy(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    
    free(tuple->elements);
    free(tuple);
}

void* tuple_get(Tuple *tuple, size_t index) {
    if (tuple == NULL || tuple->elements == NULL) {
        return NULL;
    }
    
    if (index >= tuple->count) {
        return NULL;
    }
    
    return tuple->elements[index];
}

int main(void) {
    int value1 = 10;
    int value2 = 20;
    int value3 = 30;
    
    Tuple *tuple = tuple_create(3, &value1, &value2, &value3);
    if (tuple == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }
    
    const int *first = (const int*)tuple_get(tuple, 0);
    const int *second = (const int*)tuple_get(tuple, 1);
    const int *third = (const int*)tuple_get(tuple, 2);
    
    if (first != NULL && second != NULL && third != NULL) {
        printf("First element: %d\n", *first);
        printf("Second element: %d\n", *second);
        printf("Third element: %d\n", *third);
    }
    
    const void *invalid = tuple_get(tuple, 5);
    if (invalid == NULL) {
        printf("Invalid index correctly returned NULL\n");
    }
    
    tuple_destroy(tuple);
    
    return EXIT_SUCCESS;
}