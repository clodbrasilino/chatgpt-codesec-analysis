#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

static bool product_divided_by_length(const double *numbers,
                                      size_t length,
                                      double *result)
{
    if (numbers == NULL || result == NULL || length == 0U) {
        return false;
    }

    double value = 1.0;

    for (size_t i = 0U; i < length; ++i) {
        if (!isfinite(numbers[i])) {
            return false;
        }

        if (numbers[i] != 0.0 &&
            fabs(value) > DBL_MAX / fabs(numbers[i])) {
            return false;
        }

        value *= numbers[i];
    }

    value /= (double)length;

    if (!isfinite(value)) {
        return false;
    }

    *result = value;
    return true;
}

int main(void)
{
    const double numbers[] = {2.0, 3.0, 4.0, 5.0};
    const size_t length = sizeof(numbers) / sizeof(numbers[0]);
    double result = 0.0;

    if (!product_divided_by_length(numbers, length, &result)) {
        if (fputs("Calculation failed.\n", stderr) == EOF) {
            return 2;
        }
        return 1;
    }

    if (printf("%.17g\n", result) < 0) {
        return 2;
    }

    return 0;
}