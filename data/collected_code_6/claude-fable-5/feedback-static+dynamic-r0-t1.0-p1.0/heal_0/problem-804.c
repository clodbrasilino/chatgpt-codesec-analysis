#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

bool is_product_even(const long long *numbers, size_t count)
{
    size_t i;

    if (numbers == NULL || count == 0U) {
        return false;
    }

    for (i = 0U; i < count; i++) {
        if ((numbers[i] % 2LL) == 0LL) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    size_t count = 0U;
    size_t i;
    long long *numbers = NULL;
    unsigned long input_count = 0UL;

    printf("Enter the count of numbers: ");
    if (scanf("%lu", &input_count) != 1) {
        fprintf(stderr, "Invalid input for count.\n");
        return EXIT_FAILURE;
    }

    if (input_count == 0UL || input_count > 1000000UL) {
        fprintf(stderr, "Count must be between 1 and 1000000.\n");
        return EXIT_FAILURE;
    }

    count = (size_t)input_count;

    numbers = malloc(count * sizeof(*numbers));
    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; i++) {
        printf("Enter number %zu: ", i + 1U);
        if (scanf("%lld", &numbers[i]) != 1) {
            fprintf(stderr, "Invalid number input.\n");
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    if (is_product_even(numbers, count)) {
        printf("The product is even.\n");
    } else {
        printf("The product is odd.\n");
    }

    free(numbers);
    return EXIT_SUCCESS;
}