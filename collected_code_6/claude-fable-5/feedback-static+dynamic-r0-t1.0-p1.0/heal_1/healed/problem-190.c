#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static unsigned long long absoluteDifference(long long a, long long b)
{
    if (a >= b)
    {
        return (unsigned long long)a - (unsigned long long)b;
    }
    return (unsigned long long)b - (unsigned long long)a;
}

int countIntegralPoints(long long x1, long long y1, long long x2, long long y2,
                        unsigned long long *result)
{
    unsigned long long width;
    unsigned long long height;
    unsigned long long innerWidth;
    unsigned long long innerHeight;

    width = absoluteDifference(x2, x1);
    height = absoluteDifference(y2, y1);

    if (width < 2 || height < 2)
    {
        *result = 0;
        return 0;
    }

    innerWidth = width - 1;
    innerHeight = height - 1;

    if (innerWidth > ULLONG_MAX / innerHeight)
    {
        return -1;
    }

    *result = innerWidth * innerHeight;
    return 0;
}

int main(void)
{
    long long x1;
    long long y1;
    long long x2;
    long long y2;
    unsigned long long result;

    printf("Enter bottom-left corner (x1 y1): ");
    if (scanf("%lld %lld", &x1, &y1) != 2)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter top-right corner (x2 y2): ");
    if (scanf("%lld %lld", &x2, &y2) != 2)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (countIntegralPoints(x1, y1, x2, y2, &result) != 0)
    {
        fprintf(stderr, "Result too large to represent\n");
        return EXIT_FAILURE;
    }

    printf("Number of integral coordinates inside the square: %llu\n", result);

    return EXIT_SUCCESS;
}