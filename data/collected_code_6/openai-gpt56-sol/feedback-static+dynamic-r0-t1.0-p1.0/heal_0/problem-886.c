#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

static int calculate_average(const double values[], size_t length, double *average)
{
    if (values == NULL || average == NULL || length == 0U) {
        return -1;
    }

    double sum = 0.0;

    for (size_t i = 0U; i < length; ++i) {
        sum += values[i];
    }

    *average = sum / (double)length;
    return 0;
}

int main(void)
{
    const double values[] = {10.0, 20.0, 30.0, 40.0, 50.0};
    const size_t length = sizeof(values) / sizeof(values[0]);
    double average = 0.0;

    if (calculate_average(values, length, &average) != 0) {
        fprintf(stderr, "Unable to calculate the average.\n");
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", average) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}