#include <stdio.h>
#include <complex.h>
#include <math.h>

double get_complex_angle(double complex z) {
    return carg(z);
}

int main(void) {
    double complex z1 = 1.0 + 1.0 * I;
    double complex z2 = -1.0 + 0.0 * I;
    double complex z3 = 0.0 - 1.0 * I;
    double complex z4 = 0.0 + 0.0 * I;

    double angle1 = get_complex_angle(z1);
    double angle2 = get_complex_angle(z2);
    double angle3 = get_complex_angle(z3);
    double angle4 = get_complex_angle(z4);

    printf("Angle of 1+1i: %f\n", angle1);
    printf("Angle of -1+0i: %f\n", angle2);
    printf("Angle of 0-1i: %f\n", angle3);
    printf("Angle of 0+0i: %f\n", angle4);

    return 0;
}