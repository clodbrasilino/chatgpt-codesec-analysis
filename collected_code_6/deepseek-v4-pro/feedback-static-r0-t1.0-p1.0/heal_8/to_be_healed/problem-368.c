#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

Tuple repeat_tuple(Tuple tuple, size_t n) {
    Tuple result;
    
    if (tuple.elements == NULL || tuple.size == 0 || n == 0) {
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
    
    size_t copy_size = tuple.size * sizeof(int);
    
    for (size_t i = 0; i < n; i++) {
        size_t offset = i * tuple.size;
        if (offset + tuple.size > result.size) {
            free(result.elements);
            result.elements = NULL;
            result.size = 0;
            return result;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result.elements + offset, tuple.elements, copy_size);
    }
    
    return result;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL && tuple->elements != NULL) {
        free(tuple->elements);
        tuple->elements = NULL;
        tuple->size = 0;
    }
}

int main(void) {
    /* Possible weaknesses found:
     *  The scope of the variable 'elements' can be reduced. [variableScope]
     */
    int elements[] = {1, 2, 3};
    int *heap_elements = (int *)malloc(3 * sizeof(int));
    if (heap_elements == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     *  Condition 'heap_elements!=NULL' is always true [knownConditionTrueFalse]
     */
    if (heap_elements != NULL) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(heap_elements, elements, 3 * sizeof(int));
    }
    
    Tuple original;
    original.elements = heap_elements;
    original.size = 3;
    
    Tuple repeated = repeat_tuple(original, 4);
    
    if (repeated.elements == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_tuple(&original);
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
    free_tuple(&original);
    
    return 0;
}