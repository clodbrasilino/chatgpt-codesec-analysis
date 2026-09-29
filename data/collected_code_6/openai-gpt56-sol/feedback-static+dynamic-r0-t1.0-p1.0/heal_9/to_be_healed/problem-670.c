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
    if (numbers == NULL || count < 2U) {
        return false;
    }

    size_t decreases = 0U;
    size_t increases = 0U;

    for (size_t i = 1U; i < count; ++i) {
        if (numbers[i] < numbers[i - 1U]) {
            ++decreases;
        } else if (numbers[i] > numbers[i - 1U]) {
            ++increases;
        }
    }

    return decreases > increases;
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