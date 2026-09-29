#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int sum_even_in_range(long long l, long long r, long long *out)
{
    long long first;
    long long last;
    long long count;
    long long mid;
    long long result;

    if (l > r) {
        *out = 0;
        return 0;
    }

    if (l % 2 == 0) {
        first = l;
    } else {
        if (l == LLONG_MAX) {
            *out = 0;
            return 0;
        }
        first = l + 1;
    }

    if (r % 2 == 0) {
        last = r;
    } else {
        if (r == LLONG_MIN) {
            *out = 0;
            return 0;
        }
        last = r - 1;
    }

    if (first > last) {
        *out = 0;
        return 0;
    }

    count = ((last - first) / 2) + 1;
    mid = (first / 2) + (last / 2);

    if (__builtin_mul_overflow(count, mid, &result)) {
        return -1;
    }

    *out = result;
    return 0;
}

int main(void)
{
    long long l;
    long long r;
    long long result;

    printf("Enter lower bound: ");
    if (scanf("%lld", &l) != 1) {
        fprintf(stderr, "Invalid input for lower bound\n");
        return EXIT_FAILURE;
    }

    printf("Enter upper bound: ");
    if (scanf("%lld", &r) != 1) {
        fprintf(stderr, "Invalid input for upper bound\n");
        return EXIT_FAILURE;
    }

    if (l < 1 || r < 1) {
        fprintf(stderr, "Bounds must be natural numbers (>= 1)\n");
        return EXIT_FAILURE;
    }

    if (l > r) {
        fprintf(stderr, "Lower bound must not exceed upper bound\n");
        return EXIT_FAILURE;
    }

    if (sum_even_in_range(l, r, &result) != 0) {
        fprintf(stderr, "Result overflows a 64-bit signed integer\n");
        return EXIT_FAILURE;
    }

    printf("Sum of even numbers in [%lld, %lld] = %lld\n", l, r, result);

    return EXIT_SUCCESS;
}