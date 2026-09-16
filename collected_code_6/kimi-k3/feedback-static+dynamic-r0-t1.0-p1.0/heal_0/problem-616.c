#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} IntTuple;

IntTuple *tuple_modulo(const IntTuple *tuple1, const IntTuple *tuple2) {
    if (tuple1 == NULL || tuple2 == NULL || 
        tuple1->elements == NULL || tuple2->elements == NULL ||
        tuple1->size != tuple2->size || tuple1->size == 0) {
        return NULL;
    }

    IntTuple *result = malloc(sizeof(IntTuple));
    if (result == NULL) {
        return NULL;
    }

    result->elements = malloc(tuple1->size * sizeof(int));
    if (result->elements == NULL) {
        free(result);
        return NULL;
    }

    result->size = tuple1->size;

    for (size_t i = 0; i < tuple1->size; i++) {
        if (tuple2->elements[i] == 0) {
            free(result->elements);
            free(result);
            return NULL;
        }
        result->elements[i] = tuple1->elements[i] % tuple2->elements[i];
    }

    return result;
}

void tuple_destroy(IntTuple *tuple) {
    if (tuple != NULL) {
        free(tuple->elements);
        free(tuple);
    }
}

int main(void) {
    int data1[] = {10, 20, 30, 40};
    int data2[] = {3, 4, 5, 6};
    
    IntTuple tuple1 = {data1, 4};
    IntTuple tuple2 = {data2, 4};

    IntTuple *result = tuple_modulo(&tuple1, &tuple2);
    
    if (result == NULL) {
        fprintf(stderr, "Error: Invalid input or division by zero\n");
        return EXIT_FAILURE;
    }

    printf("Result: ");
    for (size_t i = 0; i < result->size; i++) {
        printf("%d ", result->elements[i]);
    }
    printf("\n");

    tuple_destroy(result);

    return EXIT_SUCCESS;
}