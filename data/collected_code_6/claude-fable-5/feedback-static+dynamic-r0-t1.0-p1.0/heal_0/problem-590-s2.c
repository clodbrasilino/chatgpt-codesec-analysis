#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Rectangular;

typedef struct {
    double r;
    double theta;
} Polar;

int polar_to_rectangular(const Polar *p, Rectangular *rect)
{
    if (p == NULL || rect == NULL) {
        return -1;
    }
    if (!isfinite(p->r) || !isfinite(p->theta)) {
        return -1;
    }
    rect->x = p->r * cos(p->theta);
    rect->y = p->r * sin(p->theta);
    if (!isfinite(rect->x) || !isfinite(rect->y)) {
        return -1;
    }
    return 0;
}

int main(void)
{
    Polar p;
    Rectangular rect;

    printf("Enter radius: ");
    if (scanf("%lf", &p.r) != 1) {
        fprintf(stderr, "Error: invalid input for radius\n");
        return EXIT_FAILURE;
    }

    printf("Enter angle in radians: ");
    if (scanf("%lf", &p.theta) != 1) {
        fprintf(stderr, "Error: invalid input for angle\n");
        return EXIT_FAILURE;
    }

    if (polar_to_rectangular(&p, &rect) != 0) {
        fprintf(stderr, "Error: conversion failed\n");
        return EXIT_FAILURE;
    }

    printf("Rectangular coordinates: x = %f, y = %f\n", rect.x, rect.y);

    return EXIT_SUCCESS;
}