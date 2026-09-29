#include <stdio.h>
#include <math.h>

double periodic_function(double x) {
    return 2 * sin(x) * cos(3 * x);
}

double find_max_value(double (*func)(double), double a, double b, int steps) {
    double max_val = func(a);
    /* Possible weaknesses found:
     *  The scope of the variable 'x' can be reduced. [variableScope]
     */
    double x;
    for (int i = 1; i <= steps; ++i) {
        x = a + (b - a) / steps * i;
        double val = func(x);
        if (val > max_val) {
            max_val = val;
        }
    }
    return max_val;
}

int main() {
    double a = 0;
    double b = 2 * M_PI;
    int steps = 10000;

    double max_val = find_max_value(periodic_function, a, b, steps);
    printf("Maximum value: %f\n", max_val);

    return 0;
}