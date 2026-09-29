#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static bool product_is_even(const long *numbers, size_t count)
{
    size_t i;

    if (numbers == NULL || count == 0U) {
        return false;
    }

    for (i = 0U; i < count; ++i) {
        if (numbers[i] % 2L == 0L) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    size_t count;
    size_t i;
    long *numbers;

    if (scanf("%zu", &count) != 1 || count == 0U ||
        count > SIZE_MAX / sizeof(*numbers)) {
        return EXIT_FAILURE;
    }

    numbers = malloc(count * sizeof(*numbers));
    if (numbers == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (scanf("%ld", &numbers[i]) != 1) {
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    puts(product_is_even(numbers, count) ? "Even" : "Odd");

    free(numbers);
    return EXIT_SUCCESS;
}