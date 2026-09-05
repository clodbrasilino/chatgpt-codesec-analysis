#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

static unsigned long long sum_of_proper_divisors(unsigned long long n)
{
    if (n <= 1ULL) {
        return 0ULL;
    }

    unsigned long long sum = 1ULL;
    unsigned long long i;

    for (i = 2ULL; i <= n / i; ++i) {
        if (n % i == 0ULL) {
            unsigned long long complement = n / i;
            sum += i;
            if (complement != i) {
                sum += complement;
            }
        }
    }

    return sum;
}

static bool is_amicable(unsigned long long n)
{
    unsigned long long sum_n = sum_of_proper_divisors(n);

    if (sum_n == n) {
        return false;
    }

    if (sum_n == 0ULL) {
        return false;
    }

    return sum_of_proper_divisors(sum_n) == n;
}

static unsigned long long sum_amicable_numbers(unsigned long long limit)
{
    unsigned long long total = 0ULL;
    unsigned long long i;

    for (i = 1ULL; i <= limit; ++i) {
        if (is_amicable(i)) {
            if (ULLONG_MAX - total < i) {
                return ULLONG_MAX;
            }
            total += i;
        }
    }

    return total;
}

int main(void)
{
    unsigned long long limit;
    unsigned long long result;

    if (scanf("%llu", &limit) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = sum_amicable_numbers(limit);

    if (result == ULLONG_MAX) {
        fprintf(stderr, "Overflow occurred during summation\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}