#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_product_even(const int *numbers, size_t count)
{
    size_t i;

    if (numbers == NULL || count == 0U) {
        return false;
    }

    for (i = 0U; i < count; i++) {
        if ((numbers[i] % 2) == 0) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    size_t count = 0U;
    size_t i;
    int *numbers = NULL;

    printf("Enter the count of numbers: ");
    if (scanf("%zu", &count) != 1) {
        fprintf(stderr, "Invalid input for count.\n");
        return EXIT_FAILURE;
    }

    if (count == 0U || count > 1000U) {
        fprintf(stderr, "Count must be between 1 and 1000.\n");
        return EXIT_FAILURE;
    }

    numbers = malloc(count * sizeof(*numbers));
    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; i++) {
        printf("Enter number %zu: ", i + 1U);
        if (scanf("%d", &numbers[i]) != 1) {
            fprintf(stderr, "Invalid input for number.\n");
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    if (is_product_even(numbers, count)) {
        printf("The product of the numbers is even.\n");
    } else {
        printf("The product of the numbers is odd.\n");
    }

    free(numbers);
    numbers = NULL;

    return EXIT_SUCCESS;
}