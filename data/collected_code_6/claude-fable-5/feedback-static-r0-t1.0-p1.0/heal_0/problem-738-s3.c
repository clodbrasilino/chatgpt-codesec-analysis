#include <stdio.h>
#include <stdlib.h>

double geometric_sum(int n)
{
    double sum = 0.0;
    double term = 1.0;
    int i;

    for (i = 0; i <= n; i++) {
        sum += term;
        term /= 2.0;
    }

    return sum;
}

int main(void)
{
    int n = 0;
    int result;
    double sum;

    printf("Enter n: ");
    result = scanf("%d", &n);

    if (result != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Error: n must be non-negative\n");
        return EXIT_FAILURE;
    }

    sum = geometric_sum(n - 1);

    if (printf("Geometric sum: %f\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}