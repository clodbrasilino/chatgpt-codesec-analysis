#include <stdio.h>
#include <math.h>

double findMin(double (*f)(double), double start, double end, double step) {
    double min = f(start);
    double x;
    for (x = start; x <= end; x += step) {
        double val = f(x);
        if (val < min) {
            min = val;
        }
    }
    return min;
}

double periodicFunction(double x) {
    return sin(x);
}

int main() {
    double start = 0;
    double end = 2 * M_PI;
    double step = 0.01;
    double min = findMin(periodicFunction, start, end, step);
    printf("Minimum value: %f\n", min);
    return 0;
}