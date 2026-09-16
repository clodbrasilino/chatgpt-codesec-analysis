#include <errno.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>

static int calculate_standard_deviation(const double values[], size_t count,
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

    errno = 0;
    const double standard_deviation =
        sqrt(sum_squared_differences / (double)count);

    if (errno != 0 || !isfinite(standard_deviation)) {
        return -1;
    }

    *result = standard_deviation;
    return 0;
}

int main(void)
{
    const double values[] = {2.0, 4.0, 4.0, 4.0, 5.0, 5.0, 7.0, 9.0};
    const size_t count = sizeof(values) / sizeof(values[0]);
    double standard_deviation = 0.0;

    if (calculate_standard_deviation(values, count, &standard_deviation) != 0) {
        (void)fprintf(stderr, "Failed to calculate standard deviation.\n");
        return 1;
    }

    if (printf("Standard deviation: %.6f\n", standard_deviation) < 0) {
        return 1;
    }

    return 0;
}