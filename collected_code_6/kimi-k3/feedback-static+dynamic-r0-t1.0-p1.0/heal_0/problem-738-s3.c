#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

double geometric_sum(int n, double ratio)
{
    double sum = 0.0;
    double term = 1.0;
    int i;

    if (n < 1) {
        return 0.0;
    }

    for (i = 0; i < n; i++) {
        sum += term;
        term *= ratio;
    }

    return sum;
}

int main(void)
{
    int n;
    double ratio;
    double result;

    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input for n\n");
        return EXIT_FAILURE;
    }

    if (n < 1) {
        fprintf(stderr, "Error: n must be at least 1\n");
        return EXIT_FAILURE;
    }

    printf("Enter the common ratio: ");
    if (scanf("%lf", &ratio) != 1) {
        fprintf(stderr, "Error: Invalid input for ratio\n");
        return EXIT_FAILURE;
    }

    result = geometric_sum(n - 1, ratio);

    if (isnan(result) || isinf(result)) {
        fprintf(stderr, "Error: Numerical overflow or invalid result\n");
        return EXIT_FAILURE;
    }

    printf("Geometric sum of %d terms: %.10f\n", n - 1, result);

    return EXIT_SUCCESS;
}