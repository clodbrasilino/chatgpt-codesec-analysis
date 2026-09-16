#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SAMPLES 1000000L

static double periodic_function(double x)
{
    return sin(x) + cos(2.0 * x);
}

static int find_maximum(double (*f)(double), double period, long samples, double *result)
{
    long i;
    double step;
    double max_val;
    double x;
    double y;

    if (f == NULL || result == NULL) {
        return -1;
    }
    if (samples <= 0L || period <= 0.0 || !isfinite(period)) {
        return -1;
    }

    step = period / (double)samples;
    max_val = f(0.0);

    if (!isfinite(max_val)) {
        return -1;
    }

    for (i = 1L; i <= samples; i++) {
        x = step * (double)i;
        y = f(x);
        if (!isfinite(y)) {
            return -1;
        }
        if (y > max_val) {
            max_val = y;
        }
    }

    *result = max_val;
    return 0;
}

int main(void)
{
    double period;
    double maximum;
    int status;

    period = 2.0 * acos(-1.0);
    maximum = 0.0;

    status = find_maximum(periodic_function, period, SAMPLES, &maximum);
    if (status != 0) {
        if (fprintf(stderr, "Error: failed to compute maximum value\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Maximum value of the periodic function over one period: %.6f\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}