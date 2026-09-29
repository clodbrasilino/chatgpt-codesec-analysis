#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int sum_odd_up_to(long long n, long long *result)
{
    long long count;

    if (result == NULL) {
        return -1;
    }
    if (n < 1) {
        *result = 0;
        return 0;
    }
    if (n == LLONG_MAX) {
        return -1;
    }
    count = (n + 1) / 2;
    if (count > 0 && count > LLONG_MAX / count) {
        return -1;
    }
    *result = count * count;
    return 0;
}

static int sum_odd_in_range(long long l, long long r, long long *result)
{
    long long sum_r;
    long long sum_l;

    if (result == NULL) {
        return -1;
    }
    if (l > r || l < 1) {
        return -1;
    }
    if (sum_odd_up_to(r, &sum_r) != 0) {
        return -1;
    }
    if (sum_odd_up_to(l - 1, &sum_l) != 0) {
        return -1;
    }
    *result = sum_r - sum_l;
    return 0;
}

int main(void)
{
    long long l;
    long long r;
    long long sum;

    printf("Enter lower bound: ");
    if (scanf("%lld", &l) != 1) {
        fprintf(stderr, "Invalid input for lower bound.\n");
        return EXIT_FAILURE;
    }

    printf("Enter upper bound: ");
    if (scanf("%lld", &r) != 1) {
        fprintf(stderr, "Invalid input for upper bound.\n");
        return EXIT_FAILURE;
    }

    if (sum_odd_in_range(l, r, &sum) != 0) {
        fprintf(stderr, "Invalid range: bounds must be natural numbers with l <= r and the result must not overflow.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of odd natural numbers in [%lld, %lld] is %lld\n", l, r, sum);
    return EXIT_SUCCESS;
}