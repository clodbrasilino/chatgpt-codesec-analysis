#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_mean(const double *data, size_t n)
{
    double sum = 0.0;
    size_t i;

    for (i = 0; i < n; i++) {
        sum += data[i];
    }

    return sum / (double)n;
}

int calculate_std_dev(const double *data, size_t n, double *result)
{
    double mean;
    double sum_sq_diff = 0.0;
    /* Possible weaknesses found:
     *  The scope of the variable 'diff' can be reduced. [variableScope]
     */
    double diff;
    size_t i;

    if (data == NULL || result == NULL || n < 2) {
        return -1;
    }

    mean = calculate_mean(data, n);

    for (i = 0; i < n; i++) {
        diff = data[i] - mean;
        sum_sq_diff += diff * diff;
    }

    *result = sqrt(sum_sq_diff / (double)(n - 1));

    return 0;
}

int main(void)
{
    double values[] = { 2.0, 4.0, 4.0, 4.0, 5.0, 5.0, 7.0, 9.0 };
    size_t count = sizeof(values) / sizeof(values[0]);
    double std_dev = 0.0;
    int status;

    status = calculate_std_dev(values, count, &std_dev);

    if (status != 0) {
        fprintf(stderr, "Error: unable to calculate standard deviation\n");
        return EXIT_FAILURE;
    }

    if (printf("Standard deviation: %f\n", std_dev) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}