#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int safe_mul_ll(long long x, long long y, long long *result)
{
    if (x > 0) {
        if (y > 0) {
            if (x > LLONG_MAX / y) {
                return 0;
            }
        } else {
            if (y < LLONG_MIN / x) {
                return 0;
            }
        }
    } else {
        if (y > 0) {
            if (x < LLONG_MIN / y) {
                return 0;
            }
        } else {
            if (x != 0 && y < LLONG_MAX / x) {
                return 0;
            }
        }
    }
    *result = x * y;
    return 1;
}

static int safe_add_ll(long long x, long long y, long long *result)
{
    if (y > 0 && x > LLONG_MAX - y) {
        return 0;
    }
    if (y < 0 && x < LLONG_MIN - y) {
        return 0;
    }
    *result = x + y;
    return 1;
}

static int safe_sub_ll(long long x, long long y, long long *result)
{
    if (y > 0 && x < LLONG_MIN + y) {
        return 0;
    }
    if (y < 0 && x > LLONG_MAX + y) {
        return 0;
    }
    *result = x - y;
    return 1;
}

int nth_term(long long a, long long d, long long n, long long *result)
{
    long long n_minus_1;
    long long product;
    long long sum;

    if (!safe_sub_ll(n, 1LL, &n_minus_1)) {
        return 0;
    }
    if (!safe_mul_ll(n_minus_1, d, &product)) {
        return 0;
    }
    if (!safe_add_ll(a, product, &sum)) {
        return 0;
    }
    *result = sum;
    return 1;
}

int main(void)
{
    long long a;
    long long d;
    long long n;
    long long term;

    printf("Enter the first term: ");
    if (scanf("%lld", &a) != 1) {
        fprintf(stderr, "Invalid input for first term.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the common difference: ");
    if (scanf("%lld", &d) != 1) {
        fprintf(stderr, "Invalid input for common difference.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the term number: ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input for term number.\n");
        return EXIT_FAILURE;
    }

    if (n < 1) {
        fprintf(stderr, "Term number must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    if (!nth_term(a, d, n, &term)) {
        fprintf(stderr, "Arithmetic overflow: the requested term cannot be represented.\n");
        return EXIT_FAILURE;
    }

    printf("The %lld-th term is: %lld\n", n, term);

    return EXIT_SUCCESS;
}