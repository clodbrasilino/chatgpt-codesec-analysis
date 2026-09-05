#include <stdio.h>
#include <math.h>
#include <float.h>

double periodic_function(double x) {
    return sin(x) + 0.5 * cos(2 * x);
}

double find_max_periodic(double (*f)(double), double start, double end, double step) {
    if (f == NULL || step <= 0.0 || start > end) {
        return -DBL_MAX;
    }

    double max_val = -DBL_MAX;

    for (double x = start; x <= end; x += step) {
        double current_val = f(x);
        if (current_val > max_val) {
            max_val = current_val;
        }
    }

    return max_val;
}

int main(void) {
    double start = 0.0;
    double end = 2.0 * M_PI;
    double step = 0.0001;

    double max_val = find_max_periodic(periodic_function, start, end, step);

    if (max_val == -DBL_MAX) {
        return 1;
    }

    printf("%f\n", max_val);
    return 0;
}