#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

int tuple_product(const Tuple *tuple, long long *result) {
    if (tuple == NULL || result == NULL) {
        return -1;
    }
    
    if (tuple->size == 0) {
        return -1;
    }
    
    if (tuple->elements == NULL) {
        return -1;
    }
    
    *result = 1;
    for (size_t i = 0; i < tuple->size; i++) {
        *result *= tuple->elements[i];
    }
    
    return 0;
}

int main(void) {
    int numbers[] = {2, 3, 4, 5};
    Tuple tuple = {numbers, sizeof(numbers) / sizeof(numbers[0])};
    long long product = 0;
    
    if (tuple_product(&tuple, &product) == 0) {
        printf("Product: %lld\n", product);
        return 0;
    }
    
    fprintf(stderr, "Error calculating product\n");
    return 1;
}