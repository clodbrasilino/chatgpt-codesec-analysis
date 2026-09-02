#include <stdio.h>
#include <math.h>
#include <complex.h>

double get_complex_length(double complex z) {
    double real_part = creal(z);
    double imag_part = cimag(z);
    return sqrt(real_part * real_part + imag_part * imag_part);
}

int main() {
    double complex z = 3 + 4*I;
    double length = get_complex_length(z);
    printf("Length of the complex number: %f\n", length);
    return 0;
}