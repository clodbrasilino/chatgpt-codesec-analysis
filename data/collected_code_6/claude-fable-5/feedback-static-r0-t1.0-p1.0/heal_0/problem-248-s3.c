#include <stdio.h>
#include <stdlib.h>

double harmonic_sum(unsigned int n);

double harmonic_sum(unsigned int n)
{
    double sum = 0.0;
    unsigned int i;

    for (i = 1; i <= n; i++) {
        sum += 1.0 / (double)i;
    }

    return sum;
}

int main(void)
{
    unsigned int n = 0;
    double result;
    int scan_status;

    printf("Enter a positive integer n: ");
    scan_status = scanf("%u", &n);

    if (scan_status != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n < 1) {
        fprintf(stderr, "Error: n must be at least 1.\n");
        return EXIT_FAILURE;
    }

    result = harmonic_sum(n - 1);
    printf("Harmonic sum of %u is %f\n", n - 1, result);

    return EXIT_SUCCESS;
}