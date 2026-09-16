#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double complex_angle(double real, double imag)
{
    return atan2(imag, real);
}

int main(void)
{
    double real;
    double imag;
    double angle;

    printf("Enter the real part: ");
    if (scanf("%lf", &real) != 1) {
        fprintf(stderr, "Error: invalid input for real part\n");
        return EXIT_FAILURE;
    }

    printf("Enter the imaginary part: ");
    if (scanf("%lf", &imag) != 1) {
        fprintf(stderr, "Error: invalid input for imaginary part\n");
        return EXIT_FAILURE;
    }

    if (real == 0.0 && imag == 0.0) {
        fprintf(stderr, "Error: angle is undefined for zero complex number\n");
        return EXIT_FAILURE;
    }

    angle = complex_angle(real, imag);

    printf("Angle in radians: %f\n", angle);
    printf("Angle in degrees: %f\n", angle * 180.0 / M_PI);

    return EXIT_SUCCESS;
}