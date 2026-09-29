#include <stdio.h>
#include <complex.h>
#include <math.h>

double complex_length(double complex z) {
    double real = creal(z);
    double imag = cimag(z);
    return sqrt((real * real) + (imag * imag));
}

int main(void) {
    double complex z = 3.0 + 4.0 * I;
    double length = complex_length(z);
    
    if (isfinite(length)) {
        printf("%f\n", length);
    }
    
    return 0;
}