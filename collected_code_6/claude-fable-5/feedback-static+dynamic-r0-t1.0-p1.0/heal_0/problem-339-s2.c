#include <stdio.h>
#include <stdlib.h>

long long maxOccurringDivisor(long long x, long long y);

long long maxOccurringDivisor(long long x, long long y)
{
    if (x > y) {
        long long tmp = x;
        x = y;
        y = tmp;
    }
    if (x == y) {
        return x;
    }
    return 2;
}

int main(void)
{
    long long x = 0;
    long long y = 0;

    printf("Enter interval start: ");
    if (scanf("%lld", &x) != 1) {
        fprintf(stderr, "Invalid input for interval start\n");
        return EXIT_FAILURE;
    }

    printf("Enter interval end: ");
    if (scanf("%lld", &y) != 1) {
        fprintf(stderr, "Invalid input for interval end\n");
        return EXIT_FAILURE;
    }

    if (x < 1 || y < 1) {
        fprintf(stderr, "Interval bounds must be positive integers\n");
        return EXIT_FAILURE;
    }

    printf("Maximum occurring divisor in [%lld, %lld] is %lld\n",
           x, y, maxOccurringDivisor(x, y));

    return EXIT_SUCCESS;
}