#include <stdio.h>
#include <stdlib.h>

double sum_of_inverse_divisors(unsigned int n)
{
    double sum = 0.0;
    unsigned int i;

    if (n == 0U) {
        return 0.0;
    }

    for (i = 1U; i * i <= n; i++) {
        if (n % i == 0U) {
            sum += 1.0 / (double)i;
            if (i != n / i) {
                sum += 1.0 / (double)(n / i);
            }
        }
    }

    return sum;
}

int main(void)
{
    unsigned int n = 0U;
    double result;

    printf("Enter a positive integer: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (n == 0U) {
        fprintf(stderr, "Error: input must be a positive integer\n");
        return EXIT_FAILURE;
    }

    result = sum_of_inverse_divisors(n);
    printf("Sum of inverse of divisors of %u is %.6f\n", n, result);

    return EXIT_SUCCESS;
}