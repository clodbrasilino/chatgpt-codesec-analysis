#include <stdio.h>
#include <math.h>
#include <complex.h>

double complex_argument(double complex z) {
    return carg(z);
}

int main(void) {
    double complex z1 = 1.0 + 1.0*I;
    double complex z2 = -1.0 + 0.0*I;
    double complex z3 = 0.0 + 1.0*I;
    double complex z4 = 0.0 + 0.0*I;

    printf("Angle of 1+1i: %f radians\n", complex_argument(z1));
    printf("Angle of -1+0i: %f radians\n", complex_argument(z2));
    printf("Angle of 0+1i: %f radians\n", complex_argument(z3));
    printf("Angle of 0+0i: %f radians\n", complex_argument(z4));

    return 0;
}