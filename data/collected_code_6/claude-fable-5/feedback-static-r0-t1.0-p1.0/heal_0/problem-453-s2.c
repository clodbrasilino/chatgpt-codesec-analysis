#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long sum_even_factors(unsigned int n)
{
    unsigned long long sum = 0ULL;
    unsigned int i;

    if (n == 0U) {
        return 0ULL;
    }

    if ((n % 2U) != 0U) {
        return 0ULL;
    }

    for (i = 1U; i <= n / i; i++) {
        if ((n % i) == 0U) {
            if ((i % 2U) == 0U) {
                sum += (unsigned long long)i;
            }
            if (i != n / i) {
                if (((n / i) % 2U) == 0U) {
                    sum += (unsigned long long)(n / i);
                }
            }
        }
    }

    return sum;
}

int main(void)
{
    unsigned int n = 0U;
    int result;

    printf("Enter a positive integer: ");

    result = scanf("%u", &n);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n == 0U) {
        fprintf(stderr, "Error: number must be greater than zero.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of even factors of %u is %llu\n", n, sum_even_factors(n));

    return EXIT_SUCCESS;
}