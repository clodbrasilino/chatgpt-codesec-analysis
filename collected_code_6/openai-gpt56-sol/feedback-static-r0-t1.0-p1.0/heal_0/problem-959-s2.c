#include <stddef.h>
#include <stdio.h>

static int calculate_average(const double values[], size_t count, double *average)
{
    if (values == NULL || average == NULL || count == 0U) {
        return -1;
    }

    double mean = 0.0;

    for (size_t i = 0U; i < count; ++i) {
        mean += (values[i] - mean) / (double)(i + 1U);
    }

    *average = mean;
    return 0;
}

int main(void)
{
    const double values[] = {10.0, 20.0, 30.0, 40.0, 50.0};
    const size_t count = sizeof(values) / sizeof(values[0]);
    double average = 0.0;

    if (calculate_average(values, count, &average) != 0) {
        fputs("Unable to calculate the average.\n", stderr);
        return 1;
    }

    if (printf("Average: %.2f\n", average) < 0) {
        return 1;
    }

    return 0;
}