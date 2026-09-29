#include <stdio.h>
#include <stdlib.h>

int product_of_first_even_and_odd(const int *numbers, size_t count, long long *product)
{
    int first_even = 0;
    int first_odd = 0;
    int found_even = 0;
    int found_odd = 0;

    if (numbers == NULL || product == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!found_even && numbers[i] % 2 == 0) {
            first_even = numbers[i];
            found_even = 1;
        } else if (!found_odd && numbers[i] % 2 != 0) {
            first_odd = numbers[i];
            found_odd = 1;
        }

        if (found_even && found_odd) {
            *product = (long long)first_even * (long long)first_odd;
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    size_t count = 0;

    if (scanf("%zu", &count) != 1 || count == 0 ||
        count > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Invalid list size.\n");
        return EXIT_FAILURE;
    }

    int *numbers = malloc(count * sizeof(*numbers));
    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%d", &numbers[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    long long product = 0;
    if (!product_of_first_even_and_odd(numbers, count, &product)) {
        fprintf(stderr, "The list must contain both an even and an odd number.\n");
        free(numbers);
        return EXIT_FAILURE;
    }

    printf("%lld\n", product);
    free(numbers);

    return EXIT_SUCCESS;
}