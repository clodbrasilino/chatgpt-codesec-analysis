#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

double babylonian_sqrt(double n, double tolerance) {
    if (n < 0.0) {
        return NAN;
    }
    if (n == 0.0) {
        return 0.0;
    }
    if (isnan(n)) {
        return NAN;
    }
    if (isinf(n)) {
        return INFINITY;
    }

    double x = n;
    if (n > 1.0) {
        x = n / 2.0;
    }

    double prev_x;
    int iterations = 0;
    int max_iterations = 1000;

    do {
        prev_x = x;
        x = (x + n / x) / 2.0;
        iterations++;
        if (iterations >= max_iterations) {
            break;
        }
    } while (fabs(x - prev_x) > tolerance);

    return x;
}

int main(int argc, char *argv[]) {
    double inputs[] = {25.0, 2.0, 0.0, -4.0, INFINITY, NAN};
    size_t count = sizeof(inputs) / sizeof(inputs[0]);
    double tolerance = 1e-10;

    for (size_t i = 0; i < count; i++) {
        double n = inputs[i];
        double result = babylonian_sqrt(n, tolerance);
        
        if (isnan(n)) {
            printf("sqrt(NaN) = NaN\n");
        } else if (isinf(n)) {
            printf("sqrt(Inf) = Inf\n");
        } else if (n < 0.0) {
            printf("sqrt(%f) = NaN\n", n);
        } else {
            printf("sqrt(%f) = %.15f\n", n, result);
        }
    }

    return 0;
}