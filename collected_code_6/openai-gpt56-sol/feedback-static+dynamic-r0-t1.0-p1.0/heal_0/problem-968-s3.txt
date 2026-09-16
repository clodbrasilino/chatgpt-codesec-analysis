#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef double (*PeriodicFunction)(double);

static int find_periodic_maximum(PeriodicFunction function,
                                 double period,
                                 size_t samples,
                                 double tolerance,
                                 double *maximum_value,
                                 double *maximum_argument)
{
    if (function == NULL || maximum_value == NULL ||
        maximum_argument == NULL || !isfinite(period) ||
        !isfinite(tolerance) || period <= 0.0 ||
        tolerance <= 0.0 || samples < 2U) {
        return -1;
    }

    double best_x = 0.0;
    double best_value = function(0.0);

    if (!isfinite(best_value)) {
        return -1;
    }

    for (size_t i = 1U; i < samples; ++i) {
        const double x = period * (double)i / (double)samples;
        const double value = function(x);

        if (!isfinite(value)) {
            return -1;
        }

        if (value > best_value) {
            best_value = value;
            best_x = x;
        }
    }

    const double step = period / (double)samples;
    double left = best_x - step;
    double right = best_x + step;
    const double golden_ratio = (sqrt(5.0) - 1.0) / 2.0;
    size_t iterations = 0U;
    const size_t maximum_iterations = 10000U;

    while ((right - left) > tolerance && iterations < maximum_iterations) {
        const double x1 = right - golden_ratio * (right - left);
        const double x2 = left + golden_ratio * (right - left);
        const double y1 = function(remainder(x1, period));
        const double y2 = function(remainder(x2, period));

        if (!isfinite(y1) || !isfinite(y2)) {
            return -1;
        }

        if (y1 < y2) {
            left = x1;
        } else {
            right = x2;
        }

        ++iterations;
    }

    if (iterations == maximum_iterations) {
        return -1;
    }

    best_x = remainder((left + right) / 2.0, period);
    if (best_x < 0.0) {
        best_x += period;
    }

    best_value = function(best_x);
    if (!isfinite(best_value)) {
        return -1;
    }

    *maximum_value = best_value;
    *maximum_argument = best_x;
    return 0;
}

static double periodic_function(double x)
{
    return 3.0 * sin(x) + 2.0 * cos(2.0 * x);
}

int main(void)
{
    double maximum_value = 0.0;
    double maximum_argument = 0.0;
    const double period = 2.0 * acos(-1.0);

    errno = 0;

    if (find_periodic_maximum(periodic_function,
                              period,
                              10000U,
                              1.0e-12,
                              &maximum_value,
                              &maximum_argument) != 0 ||
        errno != 0) {
        fputs("Unable to determine the maximum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Maximum value: %.12f\nAt x: %.12f\n",
               maximum_value,
               maximum_argument) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}