#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-9

int are_roots_reciprocal(double a, double b, double c)
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

    result = are_roots_reciprocal(a, b, c);

    if (result == -1) {
        fprintf(stderr, "Not a valid quadratic equation (a must be non-zero)\n");
        return EXIT_FAILURE;
    }

    if (result == 1) {
        printf("The roots are reciprocal of each other.\n");
    } else {
        printf("The roots are NOT reciprocal of each other.\n");
    }

    return EXIT_SUCCESS;
}