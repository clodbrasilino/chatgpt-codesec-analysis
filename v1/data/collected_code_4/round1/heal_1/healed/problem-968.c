#include <math.h>
#include <float.h>
#include <stdio.h>

double max_periodic_value(double (*func)(double), double start, double end, double period) {
    double max = -DBL_MAX;
    for (double x = start; x <= end; x += period) {
        double value = func(x);
        if (value > max) {
            max = value;
        }
    }

    return max;
}

double function_to_optimize(double x) {
    return sin(x);
}

int main() {
    double start, end, period;
    printf("Enter start, end, period: ");
    scanf("%lf %lf %lf", &start, &end, &period);
    double max = max_periodic_value(function_to_optimize, start, end, period);
    printf("The maximum value of the function is: %.2f\n", max);

    return 0;
}