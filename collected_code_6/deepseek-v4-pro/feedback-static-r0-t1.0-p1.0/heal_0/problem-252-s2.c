#include <stdio.h>
#include <math.h>
#include <complex.h>

typedef struct {
    double magnitude;
    double angle;
} PolarCoordinate;

PolarCoordinate complex_to_polar(double complex z) {
    PolarCoordinate result;
    result.magnitude = cabs(z);
    result.angle = carg(z);
    return result;
}

int main(void) {
    double complex z1 = 3.0 + 4.0 * I;
    double complex z2 = -1.0 + 0.0 * I;
    double complex z3 = 0.0 + 0.0 * I;
    PolarCoordinate p1, p2, p3;

    p1 = complex_to_polar(z1);
    p2 = complex_to_polar(z2);
    p3 = complex_to_polar(z3);

    printf("z1: (%.2f, %.2f) -> magnitude: %.2f, angle: %.2f radians\n",
           creal(z1), cimag(z1), p1.magnitude, p1.angle);
    printf("z2: (%.2f, %.2f) -> magnitude: %.2f, angle: %.2f radians\n",
           creal(z2), cimag(z2), p2.magnitude, p2.angle);
    printf("z3: (%.2f, %.2f) -> magnitude: %.2f, angle: %.2f radians\n",
           creal(z3), cimag(z3), p3.magnitude, p3.angle);

    return 0;
}