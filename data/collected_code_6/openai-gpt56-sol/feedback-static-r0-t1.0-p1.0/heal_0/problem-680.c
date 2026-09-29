#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_increasing_trend(const double numbers[], size_t count)
{
    if (numbers == NULL || count < 2U) {
        return false;
    }

    for (size_t i = 1U; i < count; ++i) {
        if (numbers[i] <= numbers[i - 1U]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    size_t count = 0U;

    if (scanf("%zu", &count) != 1 || count < 2U ||
        count > SIZE_MAX / sizeof(double)) {
        fprintf(stderr, "Invalid sequence length.\n");
        return EXIT_FAILURE;
    }

    double *numbers = malloc(count * sizeof(*numbers));
    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%lf", &numbers[i]) != 1) {
            fprintf(stderr, "Invalid number.\n");
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    printf("%s\n", has_increasing_trend(numbers, count) ? "Increasing" : "Not increasing");

    free(numbers);
    return EXIT_SUCCESS;
}