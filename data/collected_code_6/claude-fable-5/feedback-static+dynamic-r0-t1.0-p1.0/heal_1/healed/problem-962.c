#include <stdio.h>
#include <stdlib.h>

static int sum_even_in_range(long long l, long long r, long long *result)
{
    long long first;
    long long last;
    long long count;
    long long avg;
    long long sum;

    if (l > r) {
        *result = 0;
        return 0;
    }

    if (l < 2) {
        l = 2;
    }

    if (r < 2) {
        *result = 0;
        return 0;
    }

    first = (l % 2 == 0) ? l : l + 1;
    last = (r % 2 == 0) ? r : r - 1;

    if (first > last) {
        *result = 0;
        return 0;
    }

    count = ((last - first) / 2) + 1;
    avg = first + ((last - first) / 2);

    if (__builtin_mul_overflow(count, avg, &sum)) {
        return -1;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    long long l;
    long long r;
    long long result;

    printf("Enter l and r: ");

    if (scanf("%lld %lld", &l, &r) != 2) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (l < 0 || r < 0) {
        fprintf(stderr, "Error: range must contain natural numbers only\n");
        return EXIT_FAILURE;
    }

    if (l > r) {
        fprintf(stderr, "Error: l must not exceed r\n");
        return EXIT_FAILURE;
    }

    if (sum_even_in_range(l, r, &result) != 0) {
        fprintf(stderr, "Error: result overflows long long\n");
        return EXIT_FAILURE;
    }

    printf("Sum of even numbers in [%lld, %lld] = %lld\n", l, r, result);

    return EXIT_SUCCESS;
}