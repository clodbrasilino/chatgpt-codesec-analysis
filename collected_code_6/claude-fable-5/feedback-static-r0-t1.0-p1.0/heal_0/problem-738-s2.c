#include <stdio.h>
#include <stdlib.h>

double geometric_sum(int n)
{
    double sum = 0.0;
    double term = 1.0;
    int i;

    if (n < 0) {
        return 0.0;
    }

    for (i = 0; i <= n; i++) {
        sum += term;
        term /= 2.0;
    }

    return sum;
}

int main(void)
{
    int n = 0;
    double result = 0.0;

    printf("Enter a non-negative integer n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Error: n must be non-negative\n");
        return EXIT_FAILURE;
    }

    result = geometric_sum(n);
    printf("Geometric sum for n = %d is %f\n", n, result);

    return EXIT_SUCCESS;
}