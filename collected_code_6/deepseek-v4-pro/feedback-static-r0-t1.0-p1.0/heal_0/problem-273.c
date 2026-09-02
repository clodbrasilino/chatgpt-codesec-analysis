#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

Tuple tuple_subtract(const Tuple *a, const Tuple *b) {
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
    if (tuple != NULL) {
        free(tuple->data);
        tuple->data = NULL;
        tuple->size = 0;
    }
}

int main(void) {
    size_t size = 5;
    
    Tuple tuple1;
    Tuple tuple2;
    Tuple result;
    
    tuple1.size = size;
    tuple2.size = size;
    
    tuple1.data = (int *)malloc(size * sizeof(int));
    tuple2.data = (int *)malloc(size * sizeof(int));
    
    if (tuple1.data == NULL || tuple2.data == NULL) {
        free(tuple1.data);
        free(tuple2.data);
        return 1;
    }
    
    for (size_t i = 0; i < size; i++) {
        tuple1.data[i] = (int)(i * 10);
        tuple2.data[i] = (int)(i * 3);
    }
    
    result = tuple_subtract(&tuple1, &tuple2);
    
    if (result.data == NULL) {
        tuple_free(&tuple1);
        tuple_free(&tuple2);
        return 1;
    }
    
    for (size_t i = 0; i < result.size; i++) {
        printf("%d ", result.data[i]);
    }
    printf("\n");
    
    tuple_free(&tuple1);
    tuple_free(&tuple2);
    tuple_free(&result);
    
    return 0;
}