#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int largest_adjacent_product(const int *values, size_t count, long long *result)
{
    if (values == NULL || result == NULL || count < 2U) {
        return -1;
    }

    long long largest = (long long)values[0] * values[1];

    for (size_t i = 1U; i + 1U < count; ++i) {
        const long long product = (long long)values[i] * values[i + 1U];

        if (product > largest) {
            largest = product;
        }
    }

    *result = largest;
    return 0;
}

int main(void)
{
    size_t count = 0U;

    if (printf("Enter the number of integers: ") < 0 || scanf("%zu", &count) != 1) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count < 2U || count > SIZE_MAX / sizeof(int)) {
        fputs("At least two integers are required.\n", stderr);
        return EXIT_FAILURE;
    }

    int *values = malloc(count * sizeof(*values));

    if (values == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Enter %zu integers: ", count) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            fputs("Invalid input.\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    long long result = 0;

    if (largest_adjacent_product(values, count, &result) != 0) {
        fputs("Unable to calculate the product.\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    free(values);

    if (printf("Largest adjacent product: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}