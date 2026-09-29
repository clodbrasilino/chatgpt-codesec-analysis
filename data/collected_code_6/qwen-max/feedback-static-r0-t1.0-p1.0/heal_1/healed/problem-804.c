#include <stdio.h>
#include <stdbool.h>

bool is_product_even(const int *numbers, int n) {
    for (int i = 0; i < n; ++i) {
        if (numbers[i] % 2 == 0) {
            return true;
        }
    }
    return false;
}

int main() {
    int numbers[] = {2, 3, 5, 7};
    int n = sizeof(numbers) / sizeof(numbers[0]);
    if (is_product_even(numbers, n)) {
        printf("The product is even.\n");
    } else {
        printf("The product is odd.\n");
    }
    return 0;
}