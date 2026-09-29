#include <stdio.h>
#include <stdlib.h>

static unsigned long long gcd_ull(unsigned long long a, unsigned long long b)
{
    while (b != 0ULL) {
        unsigned long long t = a % b;
        a = b;
        b = t;
    }

    return a;
}

static long long first_factorial_divisible_by(long long x)
{
    unsigned long long remaining;
    unsigned long long n;

    if (x <= 0LL) {
        return -1LL;
    }

    if (x == 1LL) {
        return 1LL;
    }

    remaining = (unsigned long long)x;

    for (n = 2ULL; n <= (unsigned long long)x; n++) {
        unsigned long long g = gcd_ull(remaining, n);
        remaining /= g;
        if (remaining == 1ULL) {
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

    printf("Enter a positive integer: ");
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

    printf("The first natural number whose factorial is divisible by %lld is %lld\n", x, result);

    return EXIT_SUCCESS;
}