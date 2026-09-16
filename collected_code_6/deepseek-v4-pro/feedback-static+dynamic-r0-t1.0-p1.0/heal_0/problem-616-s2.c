#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

Tuple tuple_modulo(const Tuple *a, const Tuple *b) {
    if (a == NULL || b == NULL || a->elements == NULL || b->elements == NULL) {
        fprintf(stderr, "Error: Null tuple or elements pointer\n");
        exit(EXIT_FAILURE);
    }
    
    if (a->size != b->size) {
        fprintf(stderr, "Error: Tuple size mismatch\n");
        exit(EXIT_FAILURE);
    }
    
    for (size_t i = 0; i < b->size; i++) {
        if (b->elements[i] == 0) {
            fprintf(stderr, "Error: Division by zero in modulo operation\n");
            exit(EXIT_FAILURE);
        }
    }
    
    Tuple result;
    result.size = a->size;
    result.elements = (int *)malloc(result.size * sizeof(int));
    
    if (result.elements == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    for (size_t i = 0; i < result.size; i++) {
        result.elements[i] = a->elements[i] % b->elements[i];
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
    int elements1[] = {10, 20, 30, 40};
    int elements2[] = {3, 7, 11, 13};
    
    Tuple tuple1 = {elements1, 4};
    Tuple tuple2 = {elements2, 4};
    
    Tuple result = tuple_modulo(&tuple1, &tuple2);
    
    printf("Result: ");
    for (size_t i = 0; i < result.size; i++) {
        printf("%d ", result.elements[i]);
    }
    printf("\n");
    
    free_tuple(&result);
    
    return 0;
}