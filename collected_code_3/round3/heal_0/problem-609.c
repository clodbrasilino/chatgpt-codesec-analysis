#include <stdio.h>
#include <math.h>

double find_min(double (*f)(double), double start, double end, double step) {
    double min_val = f(start);
    double x;
    for (x = start; x <= end; x += step) {
        double val = f(x);
        if (val < min_val) {
            min_val = val;
        }
    }
    return min_val;
}

double my_function(double x) {
    return sin(x);
}

int main() {
    double start = 0.0;
    double end = 2 * M_PI;
    double step = 0.01;
    double min_val = find_min(my_function, start, end, step);
    printf("Minimum value: %f\n", min_val);
    return 0;
}