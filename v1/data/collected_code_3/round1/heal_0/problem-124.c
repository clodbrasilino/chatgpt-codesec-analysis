#include <stdio.h>
#include <complex.h>
#include <math.h>

double getAngle(double complex z) {
    return carg(z);
}

int main() {
    double complex z = 1.0 + 1.0 * I;
    double angle = getAngle(z);
    printf("The angle of the complex number is: %f\n", angle);
    return 0;
}