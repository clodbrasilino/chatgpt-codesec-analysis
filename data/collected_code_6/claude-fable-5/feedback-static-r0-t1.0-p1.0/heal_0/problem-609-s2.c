#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double find_min_periodic(double a, double b);

double find_min_periodic(double a, double b)
{
    return -hypot(a, b);
}

int main(void)
{
    double a;
    double b;
    double result;

    printf("Enter coefficient a: ");
    if (scanf("%lf", &a) != 1) {
        fprintf(stderr, "Error: invalid input for a\n");
        return EXIT_FAILURE;
    }

    printf("Enter coefficient b: ");
    if (scanf("%lf", &b) != 1) {
        fprintf(stderr, "Error: invalid input for b\n");
        return EXIT_FAILURE;
    }

    if (!isfinite(a) || !isfinite(b)) {
        fprintf(stderr, "Error: inputs must be finite numbers\n");
        return EXIT_FAILURE;
    }

    result = find_min_periodic(a, b);

    if (!isfinite(result)) {
        fprintf(stderr, "Error: computation overflowed\n");
        return EXIT_FAILURE;
    }

    printf("Minimum value of f(x) = %g*sin(x) + %g*cos(x) is: %f\n", a, b, result);

    return EXIT_SUCCESS;
}