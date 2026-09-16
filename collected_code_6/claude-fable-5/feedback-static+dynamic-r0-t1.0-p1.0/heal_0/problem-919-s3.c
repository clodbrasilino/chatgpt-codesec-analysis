#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int multiply_list(const long long *list, size_t count, long long *result)
{
    size_t i;
    long long product;

    if (list == NULL || result == NULL) {
        return -1;
    }

    product = 1;

    for (i = 0; i < count; i++) {
        if (list[i] != 0) {
            if (product > 0 && list[i] > 0 && product > LLONG_MAX / list[i]) {
                return -1;
            }
            if (product > 0 && list[i] < 0 && list[i] < LLONG_MIN / product) {
                return -1;
            }
            if (product < 0 && list[i] > 0 && product < LLONG_MIN / list[i]) {
                return -1;
            }
            if (product < 0 && list[i] < 0 && product < LLONG_MAX / list[i]) {
                return -1;
            }
        }
        product *= list[i];
    }

    *result = product;
    return 0;
}

int main(void)
{
    long long numbers[] = {2, 3, 4, 5};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long long result;

    if (multiply_list(numbers, count, &result) != 0) {
        fprintf(stderr, "Error: multiplication failed or overflowed\n");
        return EXIT_FAILURE;
    }

    if (printf("Product: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}