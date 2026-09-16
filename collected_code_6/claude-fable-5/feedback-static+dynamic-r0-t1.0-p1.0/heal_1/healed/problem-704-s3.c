#include <stdio.h>
#include <stdlib.h>

double harmonic_sum(unsigned int n);

double harmonic_sum(unsigned int n)
{
    double sum = 0.0;
    unsigned int i;

    if (n == 0U) {
        return 0.0;
    }

    for (i = 1U; i <= n; i++) {
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

    if (n == 0U) {
        fprintf(stderr, "Error: n must be greater than zero.\n");
        return EXIT_FAILURE;
    }

    result = harmonic_sum(n);
    printf("Harmonic sum of %u is %.15f\n", n, result);

    return EXIT_SUCCESS;
}