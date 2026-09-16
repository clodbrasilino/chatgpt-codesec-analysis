#include <stdbool.h>
#include <stddef.h>
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
        fprintf(stderr, "Invalid number count.\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Input is too large.\n");
        return EXIT_FAILURE;
    }

    int *numbers = NULL;

    if (count != 0U) {
        numbers = malloc(count * sizeof(*numbers));
        if (numbers == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%d", &numbers[i]) != 1) {
            fprintf(stderr, "Invalid number.\n");
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    printf("%s\n", all_numbers_are_different(numbers, count) ? "All numbers are different." : "Duplicate numbers found.");

    free(numbers);
    return EXIT_SUCCESS;
}