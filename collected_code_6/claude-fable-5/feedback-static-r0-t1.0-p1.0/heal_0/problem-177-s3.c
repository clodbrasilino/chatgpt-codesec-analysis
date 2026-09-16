#include <stdio.h>
#include <stdlib.h>

int find_lcm_pair(long long l, long long r, long long *x, long long *y)
{
    if (l <= 0 || r <= 0 || l > r) {
        return -1;
    }
    if (2 * l <= r) {
        *x = l;
        *y = 2 * l;
        return 0;
    }
    return -1;
}

int main(void)
{
    long long l;
    long long r;
    long long x;
    long long y;

    printf("Enter range (l r): ");
    if (scanf("%lld %lld", &l, &r) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (find_lcm_pair(l, r, &x, &y) == 0) {
        printf("%lld %lld\n", x, y);
    } else {
        printf("-1 -1\n");
    }

    return EXIT_SUCCESS;
}