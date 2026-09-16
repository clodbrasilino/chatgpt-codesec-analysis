#include <stdbool.h>
#include <stdio.h>

bool is_product_even(const int *numbers, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        if (numbers[i] % 2 == 0) {
            return true;
        }
    }
    return false;
}

int main() {
    int numbers[] = {3, 7, 4, 5};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    bool result = is_product_even(numbers, count);
    printf("The product of the numbers is %s.\n", result ? "even" : "odd");
    return 0;
}