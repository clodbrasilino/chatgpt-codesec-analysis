#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

Tuple repeat_tuple(const Tuple *tuple, size_t n) {
    Tuple result;
    
    if (tuple == NULL || tuple->elements == NULL || tuple->size == 0) {
        result.elements = NULL;
        result.size = 0;
        return result;
    }
    
    if (n == 0) {
        result.elements = NULL;
        result.size = 0;
        return result;
    }
    
    if (tuple->size > SIZE_MAX / n) {
        result.elements = NULL;
        result.size = 0;
        return result;
    }
    
    result.size = tuple->size * n;
    
    if (result.size > SIZE_MAX / sizeof(int)) {
        result.elements = NULL;
        result.size = 0;
        return result;
    }
    
    result.elements = (int *)malloc(result.size * sizeof(int));
    
    if (result.elements == NULL) {
        result.size = 0;
        return result;
    }
    
    size_t source_size = tuple->size * sizeof(int);
    
    for (size_t i = 0; i < n; i++) {
        size_t offset = i * tuple->size;
        if (offset > result.size || (result.size - offset) < tuple->size) {
            free(result.elements);
            result.elements = NULL;
            result.size = 0;
            return result;
        }
        memcpy(result.elements + offset, 
               tuple->elements, 
               source_size);
    }
    
    return result;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->elements);
        tuple->elements = NULL;
        tuple->size = 0;
    }
}

int main(void) {
    int arr[] = {1, 2, 3};
    Tuple original;
    original.elements = arr;
    original.size = 3;
    
    size_t n = 4;
    Tuple repeated = repeat_tuple(&original, n);
    
    if (repeated.elements == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("Repeated tuple: ");
    for (size_t i = 0; i < repeated.size; i++) {
        printf("%d ", repeated.elements[i]);
    }
    printf("\n");
    
    free_tuple(&repeated);
    
    return 0;
}