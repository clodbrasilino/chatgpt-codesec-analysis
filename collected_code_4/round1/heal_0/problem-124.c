#include <stdio.h>
#include <math.h>
#include <complex.h>

double complexAngle(double complex z) {
    return carg(z);
}

int main() {
    double real, imag;

    printf("Enter real part of the complex number: ");
    if (scanf("%lf", &real) != 1) {
        printf("Invalid input.\n");
        return -1;
    }

    printf("Enter imaginary part of the complex number: ");
    if (scanf("%lf", &imag) != 1) {
        printf("Invalid input.\n");
        return -1;
    }

    double complex z = real + imag * I;
    double angle = complexAngle(z);

    printf("The angle of the complex number is: %lf\n", angle);

    return 0;
}