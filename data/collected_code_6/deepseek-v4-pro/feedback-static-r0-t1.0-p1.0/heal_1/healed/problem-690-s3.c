#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long multiply_consecutive(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return 0;
    }

    long long result = 1;
    int has_product = 0;

    for (size_t i = 0; i < size; i++) {
        if (list[i] == 0) {
            return 0;
        }
        if (result > LLONG_MAX / list[i]) {
            errno = ERANGE;
            return 0;
        }
        result *= list[i];
        has_product = 1;
    }

    if (!has_product) {
        return 0;
    }

    return result;
}

int main(void) {
    int numbers[] = {2, 3, 4, 5};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);

    long long product = multiply_consecutive(numbers, count);
    if (errno == ERANGE) {
        printf("Overflow detected\n");
        errno = 0;
    } else {
        printf("Product: %lld\n", product);
    }

    const int empty[] = {0};
    product = multiply_consecutive(empty, 1);
    if (errno == ERANGE) {
        printf("Overflow detected\n");
        errno = 0;
    } else {
        printf("Product with zero: %lld\n", product);
    }

    product = multiply_consecutive(NULL, 0);
    printf("Product with NULL list: %lld\n", product);

    return 0;
}