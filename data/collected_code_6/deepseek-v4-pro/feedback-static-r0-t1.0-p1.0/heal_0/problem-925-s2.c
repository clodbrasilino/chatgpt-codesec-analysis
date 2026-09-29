#include <stdio.h>

typedef struct {
    int *items;
    int size;
} Tuple;

int calculate_product(Tuple tuple) {
    if (tuple.size <= 0 || tuple.items == NULL) {
        return 0;
    }
    
    int product = 1;
    for (int i = 0; i < tuple.size; i++) {
        product *= tuple.items[i];
    }
    
    return product;
}

int main(void) {
    int numbers[] = {2, 3, 4, 5};
    Tuple tuple;
    tuple.items = numbers;
    tuple.size = 4;
    
    int result = calculate_product(tuple);
    printf("Product: %d\n", result);
    
    return 0;
}