#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Polar {
    double magnitude;
    double angle;
};

static int complex_to_polar(double real, double imag, struct Polar *result)
{
    if (result == NULL) {
        return -1;
    }

    if (!isfinite(real) || !isfinite(imag)) {
        return -1;
    }

    result->magnitude = hypot(real, imag);

    if (real == 0.0 && imag == 0.0) {
        result->angle = 0.0;
    } else {
        result->angle = atan2(imag, real);
    }

    return 0;
}

int main(void)
{
    double real;
    double imag;
    struct Polar polar;

    printf("Enter real part: ");
    if (scanf("%lf", &real) != 1) {
        fprintf(stderr, "Error: invalid input for real part\n");
        return EXIT_FAILURE;
    }

    printf("Enter imaginary part: ");
    if (scanf("%lf", &imag) != 1) {
        fprintf(stderr, "Error: invalid input for imaginary part\n");
        return EXIT_FAILURE;
    }

    if (complex_to_polar(real, imag, &polar) != 0) {
        fprintf(stderr, "Error: conversion failed\n");
        return EXIT_FAILURE;
    }

    printf("Magnitude: %f\n", polar.magnitude);
    printf("Angle (radians): %f\n", polar.angle);
    printf("Angle (degrees): %f\n", polar.angle * 180.0 / acos(-1.0));

    return EXIT_SUCCESS;
}