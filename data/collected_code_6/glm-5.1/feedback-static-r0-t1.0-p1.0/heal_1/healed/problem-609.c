#include <stdio.h>
#include <math.h>
#include <float.h>

double periodic_function(double x) {
    return sin(x) + cos(x) + sin(2 * x);
}

double find_minimum(double (*f)(double), double start, double end, double step) {
    double min_val = DBL_MAX;
    for (double x = start; x <= end; x += step) {
        double current_val = f(x);
        if (current_val < min_val) {
            min_val = current_val;
        }
    }
    return min_val;
}

int main(void) {
    double period = 2 * M_PI;
    double start = 0.0;
    double end = period;
    double step = 1e-5;
    double min_val = find_minimum(periodic_function, start, end, step);
    printf("%f\n", min_val);
    return 0;
}