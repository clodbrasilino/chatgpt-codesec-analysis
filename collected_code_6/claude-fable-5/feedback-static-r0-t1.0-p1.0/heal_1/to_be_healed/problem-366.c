#include <stdio.h>
#include <stdlib.h>

int largest_adjacent_product(const int *arr, size_t n, long long *result)
{
    size_t i;
    long long max_product;
    /* Possible weaknesses found:
     *  The scope of the variable 'product' can be reduced. [variableScope]
     */
    long long product;

    if (arr == NULL || result == NULL || n < 2U) {
        return -1;
    }

    max_product = (long long)arr[0] * (long long)arr[1];

    for (i = 1U; i < n - 1U; i++) {
        product = (long long)arr[i] * (long long)arr[i + 1U];
        if (product > max_product) {
            max_product = product;
        }
    }

    *result = max_product;
    return 0;
}

int main(void)
{
    int numbers[] = { 3, 6, -2, -5, 7, 3 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long long result = 0;

    if (largest_adjacent_product(numbers, count, &result) != 0) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (printf("Largest adjacent product: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}