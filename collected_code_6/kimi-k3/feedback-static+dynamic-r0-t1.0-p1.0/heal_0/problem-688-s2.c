#include <stdio.h>
#include <complex.h>
#include <math.h>

double complex_length(double complex z) {
    return cabs(z);
}

int main(void) {
    double complex z = 3.0 + 4.0 * I;
    printf("Length: %f\n", complex_length(z));
    return 0;
}