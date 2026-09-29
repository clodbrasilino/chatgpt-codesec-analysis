#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-9

int is_valid_triangle(double a, double b, double c) {
    if (isnan(a) || isnan(b) || isnan(c))
        return 0;
    if (isinf(a) || isinf(b) || isinf(c))
        return 0;
    if (a <= 0.0 || b <= 0.0 || c <= 0.0)
        return 0;
    if (fabs(a + b + c - 180.0) > EPSILON)
        return 0;
    return 1;
}

int main(void) {
    double angles[3];
    printf("Enter three angles in degrees: ");
    if (scanf("%lf %lf %lf", &angles[0], &angles[1], &angles[2]) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (is_valid_triangle(angles[0], angles[1], angles[2]))
        printf("Triangle with positive area is possible\n");
    else
        printf("Triangle with positive area is not possible\n");

    return EXIT_SUCCESS;
}