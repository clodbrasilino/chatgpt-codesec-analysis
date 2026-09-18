#include <stdio.h>
#include <complex.h>
#include <math.h>

double complexLength(double complex z) {
    return sqrt(pow(creal(z), 2) + pow(cimag(z), 2));
}

int main() {
    double complex z = 3 + 4*I;
    double length = complexLength(z);
    printf("Length of the complex number: %f\n", length);
    return 0;
}