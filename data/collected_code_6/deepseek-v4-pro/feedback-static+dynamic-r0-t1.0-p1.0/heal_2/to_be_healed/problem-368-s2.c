#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

Tuple repeat_tuple(const Tuple *tuple, size_t n) {
    Tuple result;
    
    if (tuple == NULL || tuple->elements == NULL || n == 0 || tuple->size == 0) {
        result.elements = NULL;
        result.size = 0;
        return result;
    }
    
    if (tuple->size > SIZE_MAX / n || (tuple->size * n) > SIZE_MAX / sizeof(int)) {
        result.elements = NULL;
        result.size = 0;
        return result;
    }
    
    result.size = tuple->size * n;
    result.elements = (int *)malloc(result.size * sizeof(int));
    
    if (result.elements == NULL) {
        result.size = 0;
        return result;
    }
    
    for (size_t i = 0; i < n; i++) {
        size_t offset = i * tuple->size;
        if (offset + tuple->size > result.size) {
            break;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result.elements + offset, 
               tuple->elements, 
               tuple->size * sizeof(int));
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
    int *heap_arr = (int *)malloc(3 * sizeof(int));
    if (heap_arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(heap_arr, arr, 3 * sizeof(int));
    
    Tuple original;
    original.elements = heap_arr;
    original.size = 3;
    
    size_t n = 4;
    Tuple repeated = repeat_tuple(&original, n);
    
    if (repeated.elements == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_tuple(&original);
        return 1;
    }
    
    printf("Repeated tuple: ");
    for (size_t i = 0; i < repeated.size; i++) {
        printf("%d ", repeated.elements[i]);
    }
    printf("\n");
    
    free_tuple(&repeated);
    free_tuple(&original);
    
    return 0;
}