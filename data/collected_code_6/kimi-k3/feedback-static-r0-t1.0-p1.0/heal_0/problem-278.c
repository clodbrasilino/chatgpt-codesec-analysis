#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

int find_element_count_before_record(const Tuple *tuple, int record, size_t *count) {
    if (tuple == NULL || tuple->elements == NULL || count == NULL) {
        return -1;
    }
    
    if (tuple->size == 0) {
        *count = 0;
        return 0;
    }
    
    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->elements[i] == record) {
            *count = i;
            return 0;
        }
    }
    
    return -1;
}

int main(void) {
    Tuple tuple;
    size_t count = 0;
    int result;
    
    tuple.size = 5;
    tuple.elements = malloc(tuple.size * sizeof(int));
    
    if (tuple.elements == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    tuple.elements[0] = 10;
    tuple.elements[1] = 20;
    tuple.elements[2] = 30;
    tuple.elements[3] = 40;
    tuple.elements[4] = 50;
    
    result = find_element_count_before_record(&tuple, 30, &count);
    
    if (result == 0) {
        printf("Element count before record: %zu\n", count);
    } else {
        printf("Record not found in tuple\n");
    }
    
    free(tuple.elements);
    tuple.elements = NULL;
    tuple.size = 0;
    
    return EXIT_SUCCESS;
}