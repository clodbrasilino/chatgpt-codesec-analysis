#include <stdio.h>
#include <math.h>
#include <float.h>
#include <errno.h>
#include <stdlib.h>

static double periodic_function(double x)
{
    return sin(x) + 0.5 * cos(2.0 * x) + 0.25 * sin(3.0 * x);
}

static double find_maximum_periodic(double period, double step, double *max_value)
{
    double x;
    double current;
    double max;
    int first;

    if (period <= 0.0 || step <= 0.0 || max_value == NULL)
    {
        errno = EINVAL;
        return -1.0;
    }

    if (!isfinite(period) || !isfinite(step))
    {
        errno = EDOM;
        return -1.0;
    }

    max = -DBL_MAX;
    first = 1;

    for (x = 0.0; x <= period; x += step)
    {
        current = periodic_function(x);

        if (!isfinite(current))
        {
            errno = ERANGE;
            return -1.0;
        }

        if (first || current > max)
        {
            max = current;
            first = 0;
        }
    }

    if (first)
    {
        errno = ERANGE;
        return -1.0;
    }

    *max_value = max;
    return 0.0;
}

int main(void)
{
    double max_value;
    double period;
    double step;
    int result;

    period = 2.0 * M_PI;
    step = 0.0001;

    result = find_maximum_periodic(period, step, &max_value);

    if (result != 0.0)
    {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    printf("Maximum value: %.10f\n", max_value);

    return EXIT_SUCCESS;
}