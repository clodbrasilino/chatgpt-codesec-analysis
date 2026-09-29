#include <stdio.h>
#include <stdlib.h>

static long long sum_odd_up_to(long long n)
{
    long long count;

    if (n < 1) {
        return 0;
    }
    count = (n + 1) / 2;
    return count * count;
}

static int sum_odd_in_range(long long l, long long r, long long *result)
{
    if (result == NULL) {
        return -1;
    }
    if (l > r || l < 1) {
        return -1;
    }
    *result = sum_odd_up_to(r) - sum_odd_up_to(l - 1);
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
        fprintf(stderr, "Invalid range: bounds must be natural numbers with l <= r.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of odd natural numbers in [%lld, %lld] is %lld\n", l, r, sum);
    return EXIT_SUCCESS;
}