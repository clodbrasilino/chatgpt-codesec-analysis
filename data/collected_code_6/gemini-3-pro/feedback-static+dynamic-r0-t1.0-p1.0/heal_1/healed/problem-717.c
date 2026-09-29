#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_standard_deviation(const double *data, size_t size) {
    if (data == NULL || size == 0) {
        return -1.0;
    }

    double sum = 0.0;
    double mean = 0.0;
    double standard_deviation = 0.0;

    for (size_t i = 0; i < size; ++i) {
        sum += data[i];
    }

    mean = sum / size;

    for (size_t i = 0; i < size; ++i) {
        standard_deviation += pow(data[i] - mean, 2);
    }

    return sqrt(standard_deviation / size);
}

int main(void) {
    size_t size = 5;
    double *data = (double *)malloc(size * sizeof(double));

    if (data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    data[0] = 10.0;
    data[1] = 20.0;
    data[2] = 30.0;
    data[3] = 40.0;
    data[4] = 50.0;

    double std_dev = calculate_standard_deviation(data, size);

    if (std_dev >= 0.0) {
        printf("Standard Deviation: %.2f\n", std_dev);
    } else {
        printf("Invalid input for standard deviation calculation.\n");
    }

    free(data);
    data = NULL;

    return 0;
}