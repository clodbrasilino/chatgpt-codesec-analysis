#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_standard_deviation(double *data, size_t n) {
    if (data == NULL || n < 1) {
        return NAN;
    }

    double mean = 0.0;
    for (size_t i = 0; i < n; ++i) {
        mean += data[i];
    }
    mean /= n;

    double variance = 0.0;
    for (size_t i = 0; i < n; ++i) {
        double diff = data[i] - mean;
        variance += diff * diff;
    }
    variance /= n;

    return sqrt(variance);
}

int main(void) {
    double data[] = {10.0, 12.0, 23.0, 23.0, 16.0, 23.0, 21.0, 16.0};
    size_t n = sizeof(data) / sizeof(data[0]);

    double std_dev = calculate_standard_deviation(data, n);

    if (!isnan(std_dev)) {
        printf("%f\n", std_dev);
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}