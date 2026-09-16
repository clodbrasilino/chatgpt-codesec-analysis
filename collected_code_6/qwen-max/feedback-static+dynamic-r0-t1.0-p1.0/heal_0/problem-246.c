#include <stdio.h>
#include <math.h>

double sqrt_babylonian(double n, double epsilon) {
    double x = n;
    double y = 1.0;

    while (x - y > epsilon) {
        x = (x + y) / 2.0;
        y = n / x;
    }

    return x;
}

int main() {
    double n = 25.0;
    double epsilon = 1e-7;
    double result = sqrt_babylonian(n, epsilon);
    printf("The square root of %f is approximately %.7f\n", n, result);
    return 0;
}