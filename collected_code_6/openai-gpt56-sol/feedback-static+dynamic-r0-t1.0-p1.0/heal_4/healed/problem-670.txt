#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_decreasing_trend(const double *numbers, size_t count)
{
    if (numbers == NULL || count < 2U) {
        return false;
    }

    for (size_t i = 1U; i < count; ++i) {
        if (numbers[i] >= numbers[i - 1U]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1 ||
        count < 2U ||
        count > SIZE_MAX / sizeof(double)) {
        return EXIT_FAILURE;
    }

    double *numbers = malloc(count * sizeof(*numbers));
    if (numbers == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%lf", &numbers[i]) != 1) {
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    bool decreasing = has_decreasing_trend(numbers, count);
    free(numbers);

    if (printf("%s\n", decreasing ? "True" : "False") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}