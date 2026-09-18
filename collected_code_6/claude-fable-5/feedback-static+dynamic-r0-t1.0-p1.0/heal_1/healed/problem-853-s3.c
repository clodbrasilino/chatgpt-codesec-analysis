#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int safe_mul(long long a, long long b, long long *out);
int safe_add(long long a, long long b, long long *out);
int sum_odd_factors(long long n, long long *out);

int safe_mul(long long a, long long b, long long *out)
{
    if (a != 0 && b > LLONG_MAX / a) {
        return 0;
    }
    *out = a * b;
    return 1;
}

int safe_add(long long a, long long b, long long *out)
{
    if (b > LLONG_MAX - a) {
        return 0;
    }
    *out = a + b;
    return 1;
}

int sum_odd_factors(long long n, long long *out)
{
    if (n <= 0) {
        *out = 0;
        return 1;
    }

    while (n % 2 == 0) {
        n /= 2;
    }

    long long result = 1;

    for (long long i = 3; i <= n / i; i += 2) {
        if (n % i == 0) {
            long long term = 1;
            long long power = 1;
            while (n % i == 0) {
                n /= i;
                if (!safe_mul(power, i, &power)) {
                    return 0;
                }
                if (!safe_add(term, power, &term)) {
                    return 0;
                }
            }
            if (!safe_mul(result, term, &result)) {
                return 0;
            }
        }
    }

    if (n > 1) {
        long long term;
        if (!safe_add(1, n, &term)) {
            return 0;
        }
        if (!safe_mul(result, term, &result)) {
            return 0;
        }
    }

    *out = result;
    return 1;
}

int main(void)
{
    long long number = 0;

    printf("Enter a positive integer: ");

    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (number <= 0) {
        fprintf(stderr, "Error: number must be positive.\n");
        return EXIT_FAILURE;
    }

    long long sum = 0;

    if (!sum_odd_factors(number, &sum)) {
        fprintf(stderr, "Error: arithmetic overflow while computing result.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of odd factors of %lld is %lld\n", number, sum);

    return EXIT_SUCCESS;
}