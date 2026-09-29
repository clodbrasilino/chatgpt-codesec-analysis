#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-9

int is_one_root_twice_other(double a, double b, double c)
{
    double lhs;
    double rhs;

    if (fabs(a) < EPSILON) {
        return -1;
    }

    lhs = 2.0 * b * b;
    rhs = 9.0 * a * c;

    if (fabs(lhs - rhs) < EPSILON * fmax(fabs(lhs), fabs(rhs)) + EPSILON) {
        return 1;
    }
    return 0;
}

int main(void)
{
    double a;
    double b;
    double c;
    double discriminant;
    int result;

    printf("Enter coefficients a, b, c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (fabs(a) < EPSILON) {
        fprintf(stderr, "Error: 'a' must be non-zero for a quadratic equation.\n");
        return EXIT_FAILURE;
    }

    discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0) {
        printf("The equation has no real roots.\n");
        return EXIT_SUCCESS;
    }

    result = is_one_root_twice_other(a, b, c);
    if (result < 0) {
        fprintf(stderr, "Error: invalid coefficients.\n");
        return EXIT_FAILURE;
    }

    if (result == 1) {
        printf("Yes, one root is twice the other.\n");
    } else {
        printf("No, one root is not twice the other.\n");
    }

    return EXIT_SUCCESS;
}