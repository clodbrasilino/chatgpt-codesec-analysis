#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

Tuple tuple_subtract(const Tuple *a, const Tuple *b) {
    if (a == NULL || b == NULL || a->data == NULL || b->data == NULL || a->size != b->size) {
        Tuple empty = {NULL, 0};
        return empty;
    }
    
    Tuple result;
    result.size = a->size;
    result.data = (int *)malloc(result.size * sizeof(int));
    
    if (result.data == NULL) {
        result.size = 0;
        return result;
    }
    
    for (size_t i = 0; i < result.size; i++) {
        result.data[i] = a->data[i] - b->data[i];
    }
    
    return result;
}

void tuple_free(Tuple *tuple) {
    if (tuple != NULL && tuple->data != NULL) {
        free(tuple->data);
        tuple->data = NULL;
        tuple->size = 0;
    }
}

int main(void) {
    int arr1[] = {10, 20, 30, 40, 50};
    int arr2[] = {1, 2, 3, 4, 5};
    
    Tuple t1 = {arr1, 5};
    Tuple t2 = {arr2, 5};
    
    Tuple result = tuple_subtract(&t1, &t2);
    
    if (result.data != NULL) {
        printf("Result: ");
        for (size_t i = 0; i < result.size; i++) {
            printf("%d ", result.data[i]);
        }
        printf("\n");
        tuple_free(&result);
    } else {
        printf("Invalid input tuples or memory allocation failed\n");
    }
    
    return 0;
}