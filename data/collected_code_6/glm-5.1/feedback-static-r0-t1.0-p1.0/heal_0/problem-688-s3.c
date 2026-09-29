#include <stdio.h>
#include <math.h>
#include <complex.h>

double get_complex_length(double complex z) {
    double real_part = creal(z);
    double imag_part = cimag(z);
    return sqrt((real_part * real_part) + (imag_part * imag_part));
}

int main(void) {
    double complex z = 3.0 + 4.0 * I;
    double length = get_complex_length(z);
    if (isfinite(length)) {
        printf("%f\n", length);
    } else {
        return 1;
    }
    return 0;
}