#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef double (*PeriodicFunction)(double);

static int find_periodic_minimum(PeriodicFunction function,
                                 double period,
                                 double tolerance,
                                 size_t samples,
                                 double *minimum_x,
                                 double *minimum_value)
{
    if (function == NULL || minimum_x == NULL || minimum_value == NULL ||
        !isfinite(period) || period <= 0.0 ||
        !isfinite(tolerance) || tolerance <= 0.0 ||
        samples < 2U) {
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

        if (value < best_value) {
            best_x = x;
            best_value = value;
        }
    }

    const double step = period / (double)samples;
    double left = best_x - step;
    double right = best_x + step;
    const double ratio = (sqrt(5.0) - 1.0) / 2.0;
    double x1 = right - ratio * (right - left);
    double x2 = left + ratio * (right - left);
    double f1 = function(x1);
    double f2 = function(x2);

    if (!isfinite(f1) || !isfinite(f2)) {
        return -1;
    }

    for (size_t iteration = 0U;
         iteration < 1000U && right - left > tolerance;
         ++iteration) {
        if (f1 <= f2) {
            right = x2;
            x2 = x1;
            f2 = f1;
            x1 = right - ratio * (right - left);
            f1 = function(x1);

            if (!isfinite(f1)) {
                return -1;
            }
        } else {
            left = x1;
            x1 = x2;
            f1 = f2;
            x2 = left + ratio * (right - left);
            f2 = function(x2);

            if (!isfinite(f2)) {
                return -1;
            }
        }
    }

    double result_x = 0.5 * (left + right);
    double result_value = function(result_x);

    if (!isfinite(result_value)) {
        return -1;
    }

    result_x = fmod(result_x, period);
    if (result_x < 0.0) {
        result_x += period;
    }

    *minimum_x = result_x;
    *minimum_value = result_value;
    return 0;
}

static double periodic_function(double x)
{
    return sin(x) + 0.5 * cos(2.0 * x);
}

int main(void)
{
    const double pi = acos(-1.0);
    double minimum_x = 0.0;
    double minimum_value = 0.0;

    errno = 0;

    if (find_periodic_minimum(periodic_function,
                              2.0 * pi,
                              1.0e-12,
                              4096U,
                              &minimum_x,
                              &minimum_value) != 0 ||
        errno != 0) {
        fputs("Failed to find the minimum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Minimum value: %.15g\nAt x: %.15g\n",
               minimum_value,
               minimum_x) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}