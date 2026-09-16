#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-9

int are_roots_reciprocal(double a, double b, double c)
{
    (void)b;
    return fabs(a - c) < EPSILON;
}

int main(void)
{
    double a;
    double b;
    double c;

    printf("Enter coefficients a, b, c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (fabs(a) < EPSILON) {
        fprintf(stderr, "Error: not a quadratic equation (a must be non-zero).\n");
        return EXIT_FAILURE;
    }

    if ((b * b) - (4.0 * a * c) < 0.0) {
        printf("The equation has no real roots.\n");
        return EXIT_SUCCESS;
    }

    if (are_roots_reciprocal(a, b, c)) {
        printf("The roots are reciprocal of each other.\n");
    } else {
        printf("The roots are not reciprocal of each other.\n");
    }

    return EXIT_SUCCESS;
}