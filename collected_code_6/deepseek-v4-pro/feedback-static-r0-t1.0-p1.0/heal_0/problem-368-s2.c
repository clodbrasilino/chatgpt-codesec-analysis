#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

Tuple repeat_tuple(const Tuple *tuple, size_t n) {
    Tuple result;
    result.size = tuple->size * n;
    result.elements = (int *)malloc(result.size * sizeof(int));
    
    if (result.elements == NULL) {
        result.size = 0;
        return result;
    }
    
    for (size_t i = 0; i < n; i++) {
        memcpy(result.elements + (i * tuple->size), 
               tuple->elements, 
               tuple->size * sizeof(int));
    }
    
    return result;
}

void free_tuple(Tuple *tuple) {
    free(tuple->elements);
    tuple->elements = NULL;
    tuple->size = 0;
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