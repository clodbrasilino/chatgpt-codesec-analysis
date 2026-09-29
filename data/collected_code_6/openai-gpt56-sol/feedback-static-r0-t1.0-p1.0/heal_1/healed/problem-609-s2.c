#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef double (*PeriodicFunction)(double, void *);

static int find_periodic_minimum(
    PeriodicFunction function,
    void *context,
    double period,
    double tolerance,
    double *minimum_x,
    double *minimum_value
) {
    const size_t samples = 4096U;
    const double golden_ratio = 0.6180339887498948482;
    const size_t max_iterations = 10000U;
    double best_value = DBL_MAX;
    double step;
    size_t best_index = 0U;

    if (function == NULL || minimum_x == NULL || minimum_value == NULL ||
        !isfinite(period) || !isfinite(tolerance) ||
        period <= 0.0 || tolerance <= 0.0) {
        return -1;
    }

    step = period / (double)samples;

    if (!isfinite(step) || step <= 0.0) {
        return -1;
    }

    for (size_t i = 0U; i < samples; ++i) {
        double x = (double)i * step;
        double value = function(x, context);

        if (!isfinite(value)) {
            return -1;
        }

        if (value < best_value) {
            best_value = value;
            best_index = i;
        }
    }

    {
        double left = ((double)best_index - 1.0) * step;
        double right = ((double)best_index + 1.0) * step;
        double x1 = right - golden_ratio * (right - left);
        double x2 = left + golden_ratio * (right - left);
        double f1 = function(remainder(x1, period), context);
        double f2 = function(remainder(x2, period), context);
        size_t iterations = 0U;
        double result_x;
        double result_value;

        if (!isfinite(f1) || !isfinite(f2)) {
            return -1;
        }

        while ((right - left) > tolerance && iterations < max_iterations) {
            if (f1 <= f2) {
                right = x2;
                x2 = x1;
                f2 = f1;
                x1 = right - golden_ratio * (right - left);
                f1 = function(remainder(x1, period), context);

                if (!isfinite(f1)) {
                    return -1;
                }
            } else {
                left = x1;
                x1 = x2;
                f1 = f2;
                x2 = left + golden_ratio * (right - left);
                f2 = function(remainder(x2, period), context);

                if (!isfinite(f2)) {
                    return -1;
                }
            }

            ++iterations;
        }

        if ((right - left) > tolerance) {
            return -1;
        }

        result_x = fmod((left + right) * 0.5, period);

        if (!isfinite(result_x)) {
            return -1;
        }

        if (result_x < 0.0) {
            result_x += period;
        }

        result_value = function(result_x, context);

        if (!isfinite(result_value)) {
            return -1;
        }

        *minimum_x = result_x;
        *minimum_value = result_value;
    }

    return 0;
}

static double periodic_function(double x, void *context) {
    (void)context;
    return sin(x) + 0.5 * cos(2.0 * x);
}

int main(void) {
    const double pi = acos(-1.0);
    double minimum_x;
    double minimum_value;

    errno = 0;

    if (!isfinite(pi) ||
        find_periodic_minimum(
            periodic_function,
            NULL,
            2.0 * pi,
            1.0e-12,
            &minimum_x,
            &minimum_value
        ) != 0 ||
        errno != 0) {
        fputs("Failed to find the minimum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf(
            "x = %.12f\nminimum = %.12f\n",
            minimum_x,
            minimum_value
        ) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}