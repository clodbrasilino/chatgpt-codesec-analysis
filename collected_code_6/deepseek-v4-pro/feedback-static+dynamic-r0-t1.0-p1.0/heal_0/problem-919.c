#include <stdio.h>
#include <stdlib.h>

int multiply_list(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return 0;
    }
    
    int result = 1;
    for (size_t i = 0; i < size; i++) {
        result *= list[i];
    }
    return result;
}

int main(void) {
    int test_list[] = {2, 3, 4, 5};
    size_t size = sizeof(test_list) / sizeof(test_list[0]);
    
    int product = multiply_list(test_list, size);
    printf("Product: %d\n", product);
    
    return 0;
}