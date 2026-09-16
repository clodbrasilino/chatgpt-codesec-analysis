#include <stdio.h>
#include <stdlib.h>

int find_lcm_pair(long long low, long long high, long long *a, long long *b)
{
    if (a == NULL || b == NULL) {
        return -1;
    }
    if (low < 1 || high < low) {
        return -1;
    }
    if (low > (high / 2)) {
        return -1;
    }
    *a = low;
    *b = 2 * low;
    return 0;
}

int main(void)
{
    long long low;
    long long high;
    long long x;
    long long y;

    printf("Enter range low and high: ");
    if (scanf("%lld %lld", &low, &high) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (find_lcm_pair(low, high, &x, &y) == 0) {
        printf("Found pair: %lld and %lld (LCM = %lld)\n", x, y, y);
    } else {
        printf("No valid pair exists in the range [%lld, %lld]\n", low, high);
    }

    return EXIT_SUCCESS;
}