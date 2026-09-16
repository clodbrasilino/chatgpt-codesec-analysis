#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected True, got 0
  *  test case 2 failed: expected False, got 1
  *  test case 0 failed: expected True, got 0
  */

static bool has_decreasing_trend(const double *numbers, size_t count)
{
    size_t i;

    if (numbers == NULL || count < 2U) {
        return false;
    }

    for (i = 1U; i < count; ++i) {
        if (!(numbers[i] < numbers[i - 1U])) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    size_t count;
    size_t i;
    double *numbers;

    if (printf("Enter the number of values: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%zu", &count) != 1 ||
        count < 2U ||
        count > SIZE_MAX / sizeof(*numbers)) {
        fprintf(stderr, "Invalid number of values.\n");
        return EXIT_FAILURE;
    }

    numbers = malloc(count * sizeof(*numbers));
    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    if (printf("Enter %zu values: ", count) < 0) {
        free(numbers);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (scanf("%lf", &numbers[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    if (has_decreasing_trend(numbers, count)) {
        if (printf("The sequence has a decreasing trend.\n") < 0) {
            free(numbers);
            return EXIT_FAILURE;
        }
    } else {
        if (printf("The sequence does not have a decreasing trend.\n") < 0) {
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    free(numbers);
    return EXIT_SUCCESS;
}