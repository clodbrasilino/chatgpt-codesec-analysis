#include <stdio.h>
#include <stdlib.h>

long long calculate_product(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 0;
    }
    
    long long product = 1;
    for (size_t i = 0; i < size; i++) {
        product *= arr[i];
    }
    return product;
}

int main(void) {
    int tuple[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    
    long long result = calculate_product(tuple, size);
    printf("Product: %lld\n", result);
    
    return 0;
}