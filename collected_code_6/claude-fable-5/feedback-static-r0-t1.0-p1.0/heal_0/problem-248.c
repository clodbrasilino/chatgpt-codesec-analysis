#include <stdio.h>
#include <stdlib.h>

double harmonic_sum(unsigned int n)
{
    double sum = 0.0;
    unsigned int i;

    if (n < 2U) {
        return 0.0;
    }

    for (i = 1U; i < n; i++) {
        sum += 1.0 / (double)i;
    }

    return sum;
}

int main(void)
{
    unsigned int n = 0U;
    double result;
    int scan_status;

    printf("Enter a positive integer n: ");
    scan_status = scanf("%u", &n);

    if (scan_status != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n < 2U) {
        fprintf(stderr, "Error: n must be at least 2.\n");
        return EXIT_FAILURE;
    }

    result = harmonic_sum(n);

    if (printf("Harmonic sum of %u is %.6f\n", n - 1U, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}