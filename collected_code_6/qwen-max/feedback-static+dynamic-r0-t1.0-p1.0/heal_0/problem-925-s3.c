#include <stdio.h>
#include <stdlib.h>

long long calculate_product(int *tuple, int len) {
    long long product = 1;
    for (int i = 0; i < len; i++) {
        product *= tuple[i];
    }
    return product;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    long long result = calculate_product(numbers, length);
    printf("Product: %lld\n", result);
    return 0;
}