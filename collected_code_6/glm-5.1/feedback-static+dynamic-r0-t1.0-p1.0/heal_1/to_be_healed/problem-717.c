#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Possible weaknesses found:
 *  Parameter 'data' can be declared as pointer to const [constParameterPointer]
 */
double calculate_standard_deviation(double *data, size_t n) {
    if (data == NULL || n == 0) {
        return -1.0;
    }

    double sum = 0.0;
    for (size_t i = 0; i < n; i++) {
        sum += data[i];
    }
    double mean = sum / n;

    double variance = 0.0;
    for (size_t i = 0; i < n; i++) {
        variance += (data[i] - mean) * (data[i] - mean);
    }
    variance /= n;

    return sqrt(variance);
}

int main(void) {
    double data[] = {10.0, 12.0, 23.0, 23.0, 16.0, 23.0, 21.0, 16.0};
    size_t n = sizeof(data) / sizeof(data[0]);

    double std_dev = calculate_standard_deviation(data, n);
    if (std_dev < 0.0) {
        return EXIT_FAILURE;
    }

    printf("%f\n", std_dev);

    return EXIT_SUCCESS;
}