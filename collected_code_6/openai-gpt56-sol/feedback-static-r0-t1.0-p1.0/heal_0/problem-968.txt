#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef double (*PeriodicFunction)(double);

static int find_periodic_maximum(
    PeriodicFunction function,
    double period,
    size_t samples,
    double *maximum_value,
    double *maximum_point
) {
    double best_value;
    double best_point;
    size_t i;

    if (function == NULL || maximum_value == NULL || maximum_point == NULL ||
        !isfinite(period) || period <= 0.0 || samples < 2U) {
        return -1;
    }

    best_point = 0.0;
    best_value = function(best_point);

    if (!isfinite(best_value)) {
        return -1;
    }

    for (i = 1U; i < samples; ++i) {
        double point = period * (double)i / (double)samples;
        double value = function(point);

        if (!isfinite(value)) {
            return -1;
        }

        if (value > best_value) {
            best_value = value;
            best_point = point;
        }
    }

    {
        double step = period / (double)samples;
        double left = best_point - step;
        double right = best_point + step;
        size_t iteration;

        for (iteration = 0U; iteration < 100U; ++iteration) {
            const double third = (right - left) / 3.0;
            const double x1 = left + third;
            const double x2 = right - third;
            const double y1 = function(x1);
            const double y2 = function(x2);

            if (!isfinite(y1) || !isfinite(y2)) {
                return -1;
            }

            if (y1 < y2) {
                left = x1;
            } else {
                right = x2;
            }
        }

        best_point = fmod((left + right) / 2.0, period);

        if (best_point < 0.0) {
            best_point += period;
        }

        best_value = function(best_point);

        if (!isfinite(best_value)) {
            return -1;
        }
    }

    *maximum_value = best_value;
    *maximum_point = best_point;
    return 0;
}

static double periodic_function(double x) {
    return 3.0 * sin(x) + 2.0 * cos(2.0 * x);
}

int main(void) {
    const double period = 2.0 * acos(-1.0);
    double maximum_value;
    double maximum_point;

    errno = 0;

    if (find_periodic_maximum(
            periodic_function,
            period,
            100000U,
            &maximum_value,
            &maximum_point
        ) != 0 || errno != 0) {
        fputs("Failed to determine the maximum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf(
            "Maximum value: %.12f\nAt x: %.12f\n",
            maximum_value,
            maximum_point
        ) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}