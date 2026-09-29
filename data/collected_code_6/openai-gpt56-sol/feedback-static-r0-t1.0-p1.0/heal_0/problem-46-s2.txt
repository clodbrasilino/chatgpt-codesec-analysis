#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool all_numbers_are_different(const int *numbers, size_t count)
{
    if (numbers == NULL && count != 0U) {
        return false;
    }

    for (size_t i = 0U; i < count; ++i) {
        for (size_t j = i + 1U; j < count; ++j) {
            if (numbers[i] == numbers[j]) {
                return false;
            }
        }
    }

    return true;
}

int main(void)
{
    size_t count = 0U;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        fputs("Input size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    int *numbers = NULL;

    if (count != 0U) {
        numbers = malloc(count * sizeof(*numbers));
        if (numbers == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%d", &numbers[i]) != 1) {
            fputs("Invalid input\n", stderr);
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    puts(all_numbers_are_different(numbers, count)
             ? "All numbers are different"
             : "Not all numbers are different");

    free(numbers);
    return EXIT_SUCCESS;
}