#include <stdio.h>
#include <stdlib.h>

static unsigned long isqrt(unsigned long n)
{
    unsigned long lo = 0;
    unsigned long hi = n;
    unsigned long ans = 0;

    while (lo <= hi) {
        unsigned long mid = lo + (hi - lo) / 2UL;

        if (mid != 0UL && mid > n / mid) {
            if (mid == 0UL) {
                break;
            }
            hi = mid - 1UL;
        } else {
            ans = mid;
            lo = mid + 1UL;
        }
    }

    return ans;
}

static unsigned long count_odd_factor_elements(unsigned long low, unsigned long high)
{
    unsigned long result = 0;

    if (low > high) {
        return 0UL;
    }

    if (low == 0UL) {
        result = isqrt(high) + 1UL;
    } else {
        result = isqrt(high) - isqrt(low - 1UL);
    }

    return result;
}

int main(void)
{
    unsigned long low = 0;
    unsigned long high = 0;
    unsigned long count = 0;

    printf("Enter lower bound: ");
    if (scanf("%lu", &low) != 1) {
        fprintf(stderr, "Invalid input for lower bound.\n");
        return EXIT_FAILURE;
    }

    printf("Enter upper bound: ");
    if (scanf("%lu", &high) != 1) {
        fprintf(stderr, "Invalid input for upper bound.\n");
        return EXIT_FAILURE;
    }

    if (low > high) {
        fprintf(stderr, "Lower bound must not exceed upper bound.\n");
        return EXIT_FAILURE;
    }

    count = count_odd_factor_elements(low, high);

    printf("Number of elements with odd factors in [%lu, %lu]: %lu\n",
           low, high, count);

    return EXIT_SUCCESS;
}