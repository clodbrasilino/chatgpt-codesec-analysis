#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <math.h>

static bool product_divided_by_length(const double values[],
                                      size_t length,
                                      double *result)
{
    if (values == NULL || result == NULL || length == 0U) {
        return false;
    }

    double product = 1.0;

    for (size_t i = 0U; i < length; ++i) {
        if (!isfinite(values[i])) {
            return false;
        }

        product *= values[i];

        if (!isfinite(product)) {
            return false;
        }
    }

    *result = product / (double)length;
    return isfinite(*result);
}

int main(void)
{
    const double numbers[] = {2.0, 3.0, 4.0, 5.0};
    const size_t length = sizeof(numbers) / sizeof(numbers[0]);
    double result = 0.0;

    if (!product_divided_by_length(numbers, length, &result)) {
        fputs("Calculation failed.\n", stderr);
        return 1;
    }

    if (printf("%.10g\n", result) < 0) {
        return 1;
    }

    return 0;
}