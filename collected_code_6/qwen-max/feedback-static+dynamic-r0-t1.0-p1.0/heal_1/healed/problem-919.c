#include <stdio.h>
#include <stdlib.h>

long multiply_items(const long *array, size_t count) {
    if (count == 0) return 0;
    long product = 1;
    for (size_t i = 0; i < count; ++i) {
        product *= array[i];
    }
    return product;
}

int main() {
    long numbers[] = {2, 3, 4, 5};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    long result = multiply_items(numbers, length);
    printf("The product is: %ld\n", result);
    return 0;
}