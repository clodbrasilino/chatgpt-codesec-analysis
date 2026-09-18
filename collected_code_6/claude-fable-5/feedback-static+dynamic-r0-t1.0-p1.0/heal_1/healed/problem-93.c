#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int safe_mul(long long x, long long y, long long *out)
{
    if (x > 0) {
        if (y > 0) {
            if (x > LLONG_MAX / y) {
                return -1;
            }
        } else {
            if (y < LLONG_MIN / x) {
                return -1;
            }
        }
    } else {
        if (y > 0) {
            if (x < LLONG_MIN / y) {
                return -1;
            }
        } else {
            if (x != 0 && y < LLONG_MAX / x) {
                return -1;
            }
        }
    }
    *out = x * y;
    return 0;
}

int power(long long base, unsigned int exp, long long *result)
{
    long long acc = 1;
    long long b = base;
    unsigned int e = exp;

    if (result == NULL) {
        return -1;
    }

    while (e > 0U) {
        if ((e & 1U) == 1U) {
            if (safe_mul(acc, b, &acc) != 0) {
                return -1;
            }
        }
        e >>= 1U;
        if (e > 0U) {
            if (safe_mul(b, b, &b) != 0) {
                return -1;
            }
        }
    }

    *result = acc;
    return 0;
}

int main(void)
{
    long long a;
    unsigned int b;
    long long result;
    int ret;

    printf("Enter base (integer): ");
    if (scanf("%lld", &a) != 1) {
        fprintf(stderr, "Invalid input for base\n");
        return EXIT_FAILURE;
    }

    printf("Enter exponent (non-negative integer): ");
    if (scanf("%u", &b) != 1) {
        fprintf(stderr, "Invalid input for exponent\n");
        return EXIT_FAILURE;
    }

    ret = power(a, b, &result);
    if (ret != 0) {
        fprintf(stderr, "Error: overflow or invalid arguments\n");
        return EXIT_FAILURE;
    }

    printf("%lld^%u = %lld\n", a, b, result);
    return EXIT_SUCCESS;
}