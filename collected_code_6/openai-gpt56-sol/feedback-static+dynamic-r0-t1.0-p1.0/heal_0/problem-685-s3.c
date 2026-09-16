#include <stdio.h>
#include <stdlib.h>

static int is_prime(unsigned long long number)
{
    unsigned long long divisor;

    if (number < 2U) {
        return 0;
    }

    if (number == 2U) {
        return 1;
    }

    if (number % 2U == 0U) {
        return 0;
    }

    for (divisor = 3U; divisor <= number / divisor; divisor += 2U) {
        if (number % divisor == 0U) {
            return 0;
        }
    }

    return 1;
}

static int sum_primes(unsigned long long n, unsigned long long *sum)
{
    unsigned long long number;
    unsigned long long result = 0U;

    if (sum == NULL) {
        return 0;
    }

    for (number = 2U; number <= n; ++number) {
        if (is_prime(number)) {
            if (result > ULLONG_MAX - number) {
                return 0;
            }
            result += number;
        }

        if (number == ULLONG_MAX) {
            break;
        }
    }

    *sum = result;
    return 1;
}

int main(void)
{
    unsigned long long n;
    unsigned long long sum;

    if (scanf("%llu", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!sum_primes(n, &sum)) {
        fprintf(stderr, "Unable to calculate the sum\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", sum);
    return EXIT_SUCCESS;
}