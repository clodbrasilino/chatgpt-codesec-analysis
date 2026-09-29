#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int safe_mul(long long a, long long b, long long *res)
{
    if (res == NULL) {
        return -1;
    }

    if (a > 0) {
        if (b > 0) {
            if (a > LLONG_MAX / b) {
                return -1;
            }
        } else if (b < 0) {
            if (b < LLONG_MIN / a) {
                return -1;
            }
        }
    } else if (a < 0) {
        if (b > 0) {
            if (a < LLONG_MIN / b) {
                return -1;
            }
        } else if (b < 0) {
            if (b < LLONG_MAX / a) {
                return -1;
            }
        }
    }

    *res = a * b;
    return 0;
}

int power(long long base, unsigned int exp, long long *result)
{
    long long acc;

    if (result == NULL) {
        return -1;
    }

    acc = 1;

    while (exp > 0U) {
        if ((exp & 1U) == 1U) {
            if (safe_mul(acc, base, &acc) != 0) {
                return -1;
            }
        }
        exp >>= 1U;
        if (exp > 0U) {
            if (safe_mul(base, base, &base) != 0) {
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

    printf("Enter base: ");
    if (scanf("%lld", &a) != 1) {
        fprintf(stderr, "Invalid input for base\n");
        return EXIT_FAILURE;
    }

    printf("Enter exponent: ");
    if (scanf("%u", &b) != 1) {
        fprintf(stderr, "Invalid input for exponent\n");
        return EXIT_FAILURE;
    }

    if (power(a, b, &result) != 0) {
        fprintf(stderr, "Overflow detected or invalid arguments\n");
        return EXIT_FAILURE;
    }

    printf("%lld^%u = %lld\n", a, b, result);
    return EXIT_SUCCESS;
}