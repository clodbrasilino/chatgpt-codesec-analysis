#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 1, got 0
  */

long long countIntegralPoints(long long x1, long long y1, long long x2, long long y2)
{
    long long width;
    long long height;

    if (x2 > x1)
    {
        width = x2 - x1;
    }
    else
    {
        width = x1 - x2;
    }

    if (y2 > y1)
    {
        height = y2 - y1;
    }
    else
    {
        height = y1 - y2;
    }

    if (width < 2 || height < 2)
    {
        return 0;
    }

    return (width - 1) * (height - 1);
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
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter top-right corner (x2 y2): ");
    if (scanf("%lld %lld", &x2, &y2) != 2)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = countIntegralPoints(x1, y1, x2, y2);
    printf("Number of integral coordinates inside the square: %lld\n", result);

    return EXIT_SUCCESS;
}