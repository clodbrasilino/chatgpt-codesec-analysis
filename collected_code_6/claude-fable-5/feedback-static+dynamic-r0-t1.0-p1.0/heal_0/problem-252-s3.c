#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double real;
    double imag;
} Complex;

typedef struct {
    double magnitude;
    double angle;
} Polar;

int complex_to_polar(const Complex *c, Polar *p)
{
    if (c == NULL || p == NULL) {
        return -1;
    }

    if (!isfinite(c->real) || !isfinite(c->imag)) {
        return -1;
    }

    p->magnitude = hypot(c->real, c->imag);

    if (!isfinite(p->magnitude)) {
        return -1;
    }

    if (c->real == 0.0 && c->imag == 0.0) {
        p->angle = 0.0;
    } else {
        p->angle = atan2(c->imag, c->real);
    }

    return 0;
}

int main(void)
{
    Complex c;
    Polar p;
    int result;

    printf("Enter real part: ");
    if (scanf("%lf", &c.real) != 1) {
        fprintf(stderr, "Error: invalid input for real part\n");
        return EXIT_FAILURE;
    }

    printf("Enter imaginary part: ");
    if (scanf("%lf", &c.imag) != 1) {
        fprintf(stderr, "Error: invalid input for imaginary part\n");
        return EXIT_FAILURE;
    }

    result = complex_to_polar(&c, &p);
    if (result != 0) {
        fprintf(stderr, "Error: conversion failed\n");
        return EXIT_FAILURE;
    }

    printf("Magnitude: %f\n", p.magnitude);
    printf("Angle (radians): %f\n", p.angle);
    printf("Angle (degrees): %f\n", p.angle * 180.0 / M_PI);

    return EXIT_SUCCESS;
}