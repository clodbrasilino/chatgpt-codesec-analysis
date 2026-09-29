#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Possible weaknesses found:
 *  Parameter 'data' can be declared as pointer to const [constParameterPointer]
 */
double calculate_standard_deviation(double *data, size_t n) {
    if (data == NULL || n == 0) {
        return NAN;
    }

    double mean = 0.0;
    for (size_t i = 0; i < n; ++i) {
        mean += data[i];
    }
    mean /= (double)n;

    double variance = 0.0;
    for (size_t i = 0; i < n; ++i) {
        double diff = data[i] - mean;
        variance += diff * diff;
    }
    variance /= (double)n;

    return sqrt(variance);
}

int main(void) {
    size_t n = 0;
    if (scanf("%zu", &n) != 1 || n == 0) {
        fprintf(stderr, "Invalid array size.\n");
        return EXIT_FAILURE;
    }

    double *data = (double *)malloc(n * sizeof(double));
    if (data == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < n; ++i) {
        if (scanf("%lf", &data[i]) != 1) {
            fprintf(stderr, "Invalid input detected.\n");
            free(data);
            return EXIT_FAILURE;
        }
    }

    double std_dev = calculate_standard_deviation(data, n);
    if (isnan(std_dev)) {
        fprintf(stderr, "Calculation error.\n");
        free(data);
        return EXIT_FAILURE;
    }

    printf("%f\n", std_dev);

    free(data);
    return EXIT_SUCCESS;
}