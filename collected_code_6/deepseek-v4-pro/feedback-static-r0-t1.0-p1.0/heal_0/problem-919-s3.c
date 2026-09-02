#include <stdio.h>
#include <stdlib.h>

long long multiply_list(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return 0;
    }
    
    long long product = 1;
    for (size_t i = 0; i < size; i++) {
        product *= list[i];
    }
    return product;
}

int main(void) {
    int numbers[] = {2, 3, 4, 5};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    
    long long result = multiply_list(numbers, count);
    printf("%lld\n", result);
    
    return 0;
}