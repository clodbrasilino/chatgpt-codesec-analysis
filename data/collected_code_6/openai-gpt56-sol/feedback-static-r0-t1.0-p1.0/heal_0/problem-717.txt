#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_standard_deviation(const double *values, size_t count,
                                        double *result)
{
    if (values == NULL || result == NULL || count == 0U) {
        return -1;
    }

    double mean = 0.0;
    double sum_squared_differences = 0.0;

    for (size_t i = 0U; i < count; ++i) {
        if (!isfinite(values[i])) {
            return -1;
        }

        const double delta = values[i] - mean;
        mean += delta / (double)(i + 1U);
        const double delta_after_update = values[i] - mean;
        sum_squared_differences += delta * delta_after_update;

        if (!isfinite(mean) || !isfinite(sum_squared_differences)) {
            return -1;
        }
    }

    *result = sqrt(sum_squared_differences / (double)count);
    return isfinite(*result) ? 0 : -1;
}

int main(void)
{
    const double values[] = {2.0, 4.0, 4.0, 4.0, 5.0, 5.0, 7.0, 9.0};
    const size_t count = sizeof(values) / sizeof(values[0]);
    double standard_deviation = 0.0;

    if (calculate_standard_deviation(values, count, &standard_deviation) != 0) {
        if (fputs("Unable to calculate standard deviation.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Standard deviation: %.6f\n", standard_deviation) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}