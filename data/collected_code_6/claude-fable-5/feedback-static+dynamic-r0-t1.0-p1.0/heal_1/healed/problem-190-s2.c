#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long countIntegralPoints(long long x1, long long y1, long long x2, long long y2)
{
    unsigned long long side_x;
    unsigned long long side_y;
    unsigned long long inner;
    unsigned long long product;

    if (x2 >= x1)
    {
        side_x = (unsigned long long)x2 - (unsigned long long)x1;
    }
    else
    {
        side_x = (unsigned long long)x1 - (unsigned long long)x2;
    }

    if (y2 >= y1)
    {
        side_y = (unsigned long long)y2 - (unsigned long long)y1;
    }
    else
    {
        side_y = (unsigned long long)y1 - (unsigned long long)y2;
    }

    if (side_x != side_y)
    {
        return -1;
    }

    if (side_x < 2)
    {
        return 0;
    }

    inner = side_x - 1ULL;

    if (inner > (unsigned long long)LLONG_MAX / inner)
    {
        return -2;
    }

    product = inner * inner;

    if (product > (unsigned long long)LLONG_MAX)
    {
        return -2;
    }

    return (long long)product;
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
        fprintf(stderr, "Invalid input for first corner\n");
        return EXIT_FAILURE;
    }

    printf("Enter top-right corner (x2 y2): ");
    if (scanf("%lld %lld", &x2, &y2) != 2)
    {
        fprintf(stderr, "Invalid input for second corner\n");
        return EXIT_FAILURE;
    }

    result = countIntegralPoints(x1, y1, x2, y2);
    if (result == -1)
    {
        fprintf(stderr, "The given coordinates do not form a square\n");
        return EXIT_FAILURE;
    }

    if (result == -2)
    {
        fprintf(stderr, "Result too large to represent\n");
        return EXIT_FAILURE;
    }

    printf("Number of integral coordinates inside the square: %lld\n", result);

    return EXIT_SUCCESS;
}