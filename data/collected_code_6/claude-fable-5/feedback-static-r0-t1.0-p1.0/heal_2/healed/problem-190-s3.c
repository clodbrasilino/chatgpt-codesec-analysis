#include <stdio.h>
#include <stdlib.h>

#define MAX_SAFE_SIDE 3037000499LL

long long countIntegralPoints(long long x1, long long y1, long long x2, long long y2);

long long countIntegralPoints(long long x1, long long y1, long long x2, long long y2)
{
    long long dx;
    long long dy;
    long long side;

    dx = (x2 >= x1) ? (x2 - x1) : (x1 - x2);
    dy = (y2 >= y1) ? (y2 - y1) : (y1 - y2);

    if (dx != dy)
    {
        return -1;
    }

    side = dx;

    if (side <= 1)
    {
        return 0;
    }

    if (side - 1 > MAX_SAFE_SIDE)
    {
        return -1;
    }

    return (side - 1) * (side - 1);
}

int main(void)
{
    long long x1;
    long long y1;
    long long x2;
    long long y2;
    long long result;

    printf("Enter bottom-left corner (x1 y1): ");
    if (scanf("%lld %lld", &x1, &y1) != 2)
    {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    printf("Enter top-right corner (x2 y2): ");
    if (scanf("%lld %lld", &x2, &y2) != 2)
    {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    result = countIntegralPoints(x1, y1, x2, y2);

    if (result < 0)
    {
        fprintf(stderr, "The given coordinates do not form a valid axis-aligned square, or the result overflows.\n");
        return EXIT_FAILURE;
    }

    printf("Number of integral coordinates strictly inside the square: %lld\n", result);

    return EXIT_SUCCESS;
}