#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-9

int roots_are_reciprocal(double a, double b, double c)
{
    (void)b;
    if (fabs(a) < EPSILON) {
        return -1;
    }
    if (fabs(a - c) < EPSILON) {
        return 1;
    }
    return 0;
}

int main(void)
{
    double a;
    double b;
    double c;
    int result;

    printf("Enter coefficients a, b, c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = roots_are_reciprocal(a, b, c);

    if (result == -1) {
        fprintf(stderr, "Not a quadratic equation (a must be non-zero)\n");
        return EXIT_FAILURE;
    }

    if (result == 1) {
        printf("The roots are reciprocal of each other\n");
    } else {
        printf("The roots are not reciprocal of each other\n");
    }

    return EXIT_SUCCESS;
}