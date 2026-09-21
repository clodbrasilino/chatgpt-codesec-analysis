#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

Tuple repeat_tuple(Tuple tuple, size_t n) {
    Tuple result;
    
    if (tuple.size == 0 || n == 0) {
        result.elements = NULL;
        result.size = 0;
        return result;
    }
    
    if (tuple.size > SIZE_MAX / n || tuple.size * n > SIZE_MAX / sizeof(int)) {
        result.elements = NULL;
        result.size = 0;
        return result;
    }
    
    result.size = tuple.size * n;
    result.elements = (int *)malloc(result.size * sizeof(int));
    
    if (result.elements == NULL) {
        result.size = 0;
        return result;
    }
    
    for (size_t i = 0; i < n; i++) {
        size_t offset = i * tuple.size;
        if (offset + tuple.size > result.size) {
            free(result.elements);
            result.elements = NULL;
            result.size = 0;
            return result;
        }
        memcpy(result.elements + offset, tuple.elements, tuple.size * sizeof(int));
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
    int elements[] = {1, 2, 3};
    Tuple original;
    original.elements = elements;
    original.size = 3;
    
    Tuple repeated = repeat_tuple(original, 4);
    
    if (repeated.elements == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("Original tuple: ");
    for (size_t i = 0; i < original.size; i++) {
        printf("%d ", original.elements[i]);
    }
    printf("\n");
    
    printf("Repeated tuple: ");
    for (size_t i = 0; i < repeated.size; i++) {
        printf("%d ", repeated.elements[i]);
    }
    printf("\n");
    
    free_tuple(&repeated);
    
    return 0;
}