#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double geometric_sum(double a, double r, int n) {
    if (n <= 0) {
        return 0.0;
    }
    if (fabs(r - 1.0) < 1e-9) {
        return a * (n - 1);
    }
    return a * (1.0 - pow(r, n - 1)) / (1.0 - r);
}

int main(void) {
    double a = 2.0;
    double r = 0.5;
    int n = 5;

    double result = geometric_sum(a, r, n);
    printf("The geometric sum of %d-1 elements is: %f\n", n, result);

    return 0;
}