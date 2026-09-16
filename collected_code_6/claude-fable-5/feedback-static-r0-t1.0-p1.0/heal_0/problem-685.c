#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool is_prime(unsigned int num)
{
    if (num < 2U) {
        return false;
    }
    if (num == 2U) {
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

static unsigned long long sum_of_primes(unsigned int n)
{
    unsigned long long sum = 0ULL;

    for (unsigned int i = 2U; i <= n; i++) {
        if (is_prime(i)) {
            sum += (unsigned long long)i;
        }
    }
    return sum;
}

int main(void)
{
    unsigned int n = 0U;
    int scan_result;

    printf("Enter n: ");
    scan_result = scanf("%u", &n);

    if (scan_result != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n > 100000U) {
        fprintf(stderr, "Input too large. Maximum allowed is 100000.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of primes from 1 to %u is %llu\n", n, sum_of_primes(n));

    return EXIT_SUCCESS;
}