#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static long long gcd(long long a, long long b)
{
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

static int lcm(long long a, long long b, long long *result)
{
    long long g;
    long long quotient;

    if (a == 0 || b == 0) {
        *result = 0;
        return 1;
    }

    g = gcd(a, b);
    quotient = a / g;

    if (quotient > 0 && b > 0) {
        if (quotient > LLONG_MAX / b) {
            return 0;
        }
    } else if (quotient > 0 && b < 0) {
        if (b < LLONG_MIN / quotient) {
            return 0;
        }
    } else if (quotient < 0 && b > 0) {
        if (quotient < LLONG_MIN / b) {
            return 0;
        }
    } else if (quotient < 0 && b < 0) {
        if (quotient < LLONG_MAX / b) {
            return 0;
        }
    }

    *result = quotient * b;
    return 1;
}

long long smallest_multiple(int n)
{
    long long result;
    long long temp;
    int i;

    if (n <= 0) {
        return 0;
    }

    result = 1;
    for (i = 2; i <= n; i++) {
        if (!lcm(result, (long long)i, &temp)) {
            return -1;
        }
        result = temp;
    }

    return result;
}

int main(void)
{
    int n;
    long long result;

    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n <= 0) {
        fprintf(stderr, "Error: n must be a positive integer\n");
        return EXIT_FAILURE;
    }

    result = smallest_multiple(n);
    if (result == -1) {
        fprintf(stderr, "Error: Overflow detected\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}