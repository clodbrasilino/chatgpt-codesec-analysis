#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double find_max_periodic(double (*func)(double), double lower, double upper, double step) {
    if (func == NULL || lower >= upper || step <= 0.0) {
        return NAN;
    }

    double max_val = func(lower);
    if (isnan(max_val)) {
        return NAN;
    }

    double current = lower + step;
    while (current <= upper) {
        double val = func(current);
        if (isnan(val)) {
            return NAN;
        }
        if (val > max_val) {
            max_val = val;
        }
        current += step;
    }

    double val = func(upper);
    if (isnan(val)) {
        return NAN;
    }
    if (val > max_val) {
        max_val = val;
    }

    return max_val;
}

double periodic_func(double x) {
    return sin(x) + cos(x * 0.5);
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    double lower = 0.0;
    double upper = 20.0 * M_PI;
    double step = 0.0001;

    double max_val = find_max_periodic(periodic_func, lower, upper, step);

    if (isnan(max_val)) {
        return EXIT_FAILURE;
    }

    printf("%f\n", max_val);

    return EXIT_SUCCESS;
}