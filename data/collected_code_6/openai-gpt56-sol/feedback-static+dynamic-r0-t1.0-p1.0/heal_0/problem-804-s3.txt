#include <stdio.h>
#include <stdlib.h>

static int is_product_even(const long long *numbers, size_t count)
{
    size_t i;

    if (numbers == NULL || count == 0U) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        if (numbers[i] % 2LL == 0LL) {
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    long long *numbers = NULL;
    size_t count;
    size_t i;
    int result;

    if (printf("Enter the number of values: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%zu", &count) != 1 || count == 0U ||
        count > SIZE_MAX / sizeof(*numbers)) {
        fprintf(stderr, "Invalid number of values.\n");
        return EXIT_FAILURE;
    }

    numbers = malloc(count * sizeof(*numbers));
    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    if (printf("Enter %zu integers: ", count) < 0) {
        free(numbers);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (scanf("%lld", &numbers[i]) != 1) {
            fprintf(stderr, "Invalid integer input.\n");
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    result = is_product_even(numbers, count);
    free(numbers);

    if (result < 0) {
        fprintf(stderr, "Unable to determine parity.\n");
        return EXIT_FAILURE;
    }

    if (printf("The product is %s.\n", result != 0 ? "even" : "odd") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}