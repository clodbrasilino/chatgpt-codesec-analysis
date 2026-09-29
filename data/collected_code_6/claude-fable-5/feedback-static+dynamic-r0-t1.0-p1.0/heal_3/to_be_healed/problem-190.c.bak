#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int countIntegralPoints(long long x1, long long y1, long long x2, long long y2, unsigned long long *result)
{
    unsigned long long width;
    unsigned long long height;
    unsigned long long a;
    unsigned long long b;

    if (x2 > x1)
    {
        width = (unsigned long long)x2 - (unsigned long long)x1;
    }
    else
    {
        width = (unsigned long long)x1 - (unsigned long long)x2;
    }

    if (y2 > y1)
    {
        height = (unsigned long long)y2 - (unsigned long long)y1;
    }
    else
    {
        height = (unsigned long long)y1 - (unsigned long long)y2;
    }

    if (width == 0 && height == 0)
    {
        *result = 1;
        return 0;
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'width<2' is not redundant
     */
    if (width < 2 || height < 2)
    {
        *result = 0;
        return 0;
    }

    /* Possible weaknesses found:
     *  Assignment 'a=width-1', assigned value is greater than 0
     */
    a = width - 1;
    b = height - 1;

    /* Possible weaknesses found:
     *  Condition 'a!=0' is always true
     *  Condition 'a!=0' is always true [knownConditionTrueFalse]
     */
    if (a != 0 && b > ULLONG_MAX / a)
    {
        return -1;
    }

    *result = a * b;
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
        fprintf(stderr, "Result overflow\n");
        return EXIT_FAILURE;
    }

    printf("Number of integral coordinates inside the square: %llu\n", result);

    return EXIT_SUCCESS;
}