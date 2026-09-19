#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef double (*PeriodicFunction)(double);

static int find_periodic_minimum(
    PeriodicFunction function,
    double period,
    size_t iterations,
    double *minimum_x,
    double *minimum_value)
{
    const double ratio = 0.5 * (sqrt(5.0) - 1.0);
    double left;
    double right;
    double x1;
    double x2;
    double value1;
    double value2;

    if (function == NULL || minimum_x == NULL || minimum_value == NULL ||
        !isfinite(period) || period <= 0.0 || iterations == 0U) {
        return -1;
    }

    left = 0.0;
    right = period;
    x1 = right - ratio * (right - left);
    x2 = left + ratio * (right - left);
    value1 = function(x1);
    value2 = function(x2);

    if (!isfinite(value1) || !isfinite(value2)) {
        return -1;
    }

    for (size_t i = 0U; i < iterations; ++i) {
        if (value1 <= value2) {
            right = x2;
            x2 = x1;
            value2 = value1;
            x1 = right - ratio * (right - left);
            value1 = function(x1);

            if (!isfinite(value1)) {
                return -1;
            }
        } else {
            left = x1;
            x1 = x2;
            value1 = value2;
            x2 = left + ratio * (right - left);
            value2 = function(x2);

            if (!isfinite(value2)) {
                return -1;
            }
        }
    }

    *minimum_x = 0.5 * (left + right);
    *minimum_value = function(*minimum_x);

    return isfinite(*minimum_value) ? 0 : -1;
}

static double periodic_function(double x)
{
    return sin(x) + 0.25 * cos(2.0 * x);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[const])
{
    double period = 2.0 * acos(-1.0);
    double minimum_x;
    double minimum_value;

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [period]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argc == 2) {
        char *end = NULL;

        errno = 0;
        period = strtod(argv[1], &end);

        if (errno != 0 || end == argv[1] || *end != '\0' ||
            !isfinite(period) || period <= 0.0) {
            fprintf(stderr, "Invalid period\n");
            return EXIT_FAILURE;
        }
    }

    if (find_periodic_minimum(
            periodic_function,
            period,
            200U,
            &minimum_x,
            &minimum_value) != 0) {
        fprintf(stderr, "Unable to determine the minimum\n");
        return EXIT_FAILURE;
    }

    printf("Minimum value: %.17g\n", minimum_value);
    printf("At x: %.17g\n", minimum_x);

    return EXIT_SUCCESS;
}