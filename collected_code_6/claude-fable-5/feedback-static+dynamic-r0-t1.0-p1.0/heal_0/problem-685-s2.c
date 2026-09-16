#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool is_prime(unsigned int num)
{
    if (num < 2U) {
        return false;
    }
    if (num < 4U) {
        return true;
    }
    if ((num % 2U) == 0U) {
        return false;
    }
    for (unsigned int i = 3U; (i * i) <= num; i += 2U) {
        if ((num % i) == 0U) {
            return false;
        }
    }
    return true;
}

static int sum_of_primes(unsigned int n, unsigned long long *result)
{
    if (result == NULL) {
        return -1;
    }
    unsigned long long sum = 0ULL;
    for (unsigned int i = 2U; i <= n; i++) {
        if (is_prime(i)) {
            sum += (unsigned long long)i;
        }
    }
    *result = sum;
    return 0;
}

int main(void)
{
    unsigned int n = 0U;
    unsigned long long sum = 0ULL;

    printf("Enter n: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (n > 1000000U) {
        fprintf(stderr, "Error: n too large (max 1000000)\n");
        return EXIT_FAILURE;
    }

    if (sum_of_primes(n, &sum) != 0) {
        fprintf(stderr, "Error: computation failed\n");
        return EXIT_FAILURE;
    }

    printf("Sum of primes between 1 and %u is %llu\n", n, sum);
    return EXIT_SUCCESS;
}