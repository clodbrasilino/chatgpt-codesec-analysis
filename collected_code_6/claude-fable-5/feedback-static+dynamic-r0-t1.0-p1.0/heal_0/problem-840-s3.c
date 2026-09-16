#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

int roots_equal_opposite(double a, double b, double c, int *result)
{
    double discriminant;

    if (result == NULL) {
        return -1;
    }

    if (fabs(a) < DBL_EPSILON) {
        return -1;
    }

    discriminant = (b * b) - (4.0 * a * c);

    if (discriminant < 0.0) {
        return -1;
    }

    if (fabs(b) < DBL_EPSILON && discriminant > 0.0) {
        *result = 1;
    } else {
        *result = 0;
    }

    return 0;
}

int main(void)
{
    double a;
    double b;
    double c;
    int result;
    int status;

    printf("Enter coefficient a: ");
    if (scanf("%lf", &a) != 1) {
        fprintf(stderr, "Invalid input for a\n");
        return EXIT_FAILURE;
    }

    printf("Enter coefficient b: ");
    if (scanf("%lf", &b) != 1) {
        fprintf(stderr, "Invalid input for b\n");
        return EXIT_FAILURE;
    }

    printf("Enter coefficient c: ");
    if (scanf("%lf", &c) != 1) {
        fprintf(stderr, "Invalid input for c\n");
        return EXIT_FAILURE;
    }

    status = roots_equal_opposite(a, b, c, &result);

    if (status != 0) {
        fprintf(stderr, "Cannot evaluate: equation is not quadratic or roots are not real\n");
        return EXIT_FAILURE;
    }

    if (result == 1) {
        printf("The roots are numerically equal and opposite in sign\n");
    } else {
        printf("The roots are not numerically equal and opposite in sign\n");
    }

    return EXIT_SUCCESS;
}