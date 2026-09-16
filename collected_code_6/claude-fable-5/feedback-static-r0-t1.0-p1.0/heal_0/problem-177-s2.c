#include <stdio.h>
#include <stdlib.h>

int find_pair_with_lcm_in_range(long long l, long long r, long long *a, long long *b)
{
    if (a == NULL || b == NULL) {
        return 0;
    }
    if (l < 1 || r < l) {
        return 0;
    }
    if (2 * l <= r) {
        *a = l;
        *b = 2 * l;
        return 1;
    }
    return 0;
}

int main(void)
{
    long long l = 0;
    long long r = 0;
    long long x = 0;
    long long y = 0;

    printf("Enter range (l r): ");
    if (scanf("%lld %lld", &l, &r) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (l < 1 || r < 1 || l > r) {
        fprintf(stderr, "Invalid range\n");
        return EXIT_FAILURE;
    }

    if (find_pair_with_lcm_in_range(l, r, &x, &y)) {
        printf("Found pair: %lld and %lld (LCM = %lld)\n", x, y, y);
    } else {
        printf("No such pair exists in the range [%lld, %lld]\n", l, r);
    }

    return EXIT_SUCCESS;
}