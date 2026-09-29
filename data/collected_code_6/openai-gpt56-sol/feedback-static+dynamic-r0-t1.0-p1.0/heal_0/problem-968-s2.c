#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef double (*PeriodicFunction)(double);

static int find_periodic_maximum(PeriodicFunction function,
                                 double period,
                                 size_t samples,
                                 double tolerance,
                                 double *maximum)
{
    if (function == NULL || maximum == NULL ||
        !isfinite(period) || period <= 0.0 ||
        samples < 2U || !isfinite(tolerance) || tolerance <= 0.0) {
        return 0;
    }

    double best_x = 0.0;
    double best_value = function(0.0);

    if (!isfinite(best_value)) {
        return 0;
    }

    const double step = period / (double)samples;

    for (size_t i = 1U; i < samples; ++i) {
        const double x = step * (double)i;
        const double value = function(x);

        if (!isfinite(value)) {
            return 0;
        }

        if (value > best_value) {
            best_value = value;
            best_x = x;
        }
    }

    double left = best_x - step;
    double right = best_x + step;
    const double ratio = (sqrt(5.0) - 1.0) / 2.0;

    while (right - left > tolerance) {
        const double x1 = right - ratio * (right - left);
        const double x2 = left + ratio * (right - left);
        const double y1 = function(fmod(x1 + period, period));
        const double y2 = function(fmod(x2 + period, period));

        if (!isfinite(y1) || !isfinite(y2)) {
            return 0;
        }

        if (y1 < y2) {
            left = x1;
        } else {
            right = x2;
        }
    }

    const double candidate = function(fmod((left + right) * 0.5 + period, period));

    if (!isfinite(candidate)) {
        return 0;
    }

    *maximum = fmax(best_value, candidate);
    return 1;
}

static double periodic_function(double x)
{
    return 3.0 * sin(x) + 2.0 * cos(2.0 * x);
}

int main(void)
{
    double maximum = 0.0;

    errno = 0;
    const int success = find_periodic_maximum(
        periodic_function,
        2.0 * acos(-1.0),
        10000U,
        1.0e-12,
        &maximum
    );

    if (!success || errno != 0) {
        fputs("Failed to determine the maximum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.12f\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}