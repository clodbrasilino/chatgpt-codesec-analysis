#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double findMinValue(double a, double b)
{
    return -sqrt((a * a) + (b * b));
}

int main(void)
{
    double a = 0.0;
    double b = 0.0;
    double result = 0.0;

    printf("Enter coefficients a and b for f(x) = a*sin(x) + b*cos(x): ");

    if (scanf("%lf %lf", &a, &b) != 2)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!isfinite(a) || !isfinite(b))
    {
        fprintf(stderr, "Error: input values must be finite numbers.\n");
        return EXIT_FAILURE;
    }

    result = findMinValue(a, b);

    if (!isfinite(result))
    {
        fprintf(stderr, "Error: computation overflowed.\n");
        return EXIT_FAILURE;
    }

    printf("Minimum possible value of f(x) = %.6f\n", result);

    return EXIT_SUCCESS;
}