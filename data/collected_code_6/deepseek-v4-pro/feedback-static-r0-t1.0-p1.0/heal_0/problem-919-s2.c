#include <stdio.h>
#include <stdlib.h>

int multiply_list(int *list, size_t size, int *result) {
    if (list == NULL || result == NULL) {
        return -1;
    }

    if (size == 0) {
        return -1;
    }

    int product = 1;
    for (size_t i = 0; i < size; i++) {
        if (__builtin_mul_overflow(product, list[i], &product)) {
            return -1;
        }
    }

    *result = product;
    return 0;
}

int main(void) {
    int list[] = {2, 3, 4, 5};
    size_t size = sizeof(list) / sizeof(list[0]);
    int result = 0;

    if (multiply_list(list, size, &result) == 0) {
        printf("Product: %d\n", result);
    } else {
        printf("Overflow occurred or invalid input\n");
    }

    return 0;
}