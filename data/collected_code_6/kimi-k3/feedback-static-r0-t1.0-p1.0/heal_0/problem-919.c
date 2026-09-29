#include <stdio.h>
#include <stdlib.h>

double multiply_all_items(const double *list, size_t count) {
    double result = 1.0;
    size_t i;

    if (list == NULL || count == 0) {
        return 0.0;
    }

    for (i = 0; i < count; i++) {
        result *= list[i];
    }

    return result;
}

int main(void) {
    double numbers[] = {2.0, 3.0, 4.0, 5.0};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    double product;

    product = multiply_all_items(numbers, count);
    printf("Product: %.2f\n", product);

    return 0;
}