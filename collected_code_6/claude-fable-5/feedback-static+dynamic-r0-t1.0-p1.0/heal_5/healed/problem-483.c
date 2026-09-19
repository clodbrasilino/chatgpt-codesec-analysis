#include <stdio.h>
#include <stdlib.h>

static unsigned long long addmod(unsigned long long a, unsigned long long b, unsigned long long m)
{
    a %= m;
    b %= m;
    if (a >= m - b) {
        return a - (m - b);
    }
    return a + b;
}

static unsigned long long mulmod(unsigned long long a, unsigned long long b, unsigned long long m)
{
    unsigned long long result = 0ULL;

    a %= m;
    b %= m;
    while (b > 0ULL) {
        if (b & 1ULL) {
            result = addmod(result, a, m);
        }
        a = addmod(a, a, m);
        b >>= 1;
    }

    return result;
}

static long long first_factorial_divisible_by(long long x)
{
    unsigned long long remainder;
    unsigned long long ux;
    unsigned long long n;

    if (x <= 0LL) {
        return -1LL;
    }

    if (x == 1LL) {
        return 1LL;
    }

    ux = (unsigned long long)x;
    remainder = 1ULL;
    for (n = 1ULL; n <= ux; n++) {
        remainder = mulmod(remainder, n, ux);
        if (remainder == 0ULL) {
            return (long long)n;
        }
    }

    return -1LL;
}

int main(void)
{
    long long x;
    long long result;
    int scan_status;

    scan_status = scanf("%lld", &x);
    if (scan_status != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (x <= 0LL) {
        fprintf(stderr, "Error: input must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    result = first_factorial_divisible_by(x);
    if (result < 0LL) {
        fprintf(stderr, "Error: could not compute result.\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}