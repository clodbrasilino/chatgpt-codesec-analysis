#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

static bool multiply_integers(int a, int b, int *result)
{
    long long multiplicand;
    long long multiplier;
    long long product = 0;
    long long limit;
    bool negative;

    if (result == NULL)
    {
        return false;
    }

    negative = ((a < 0) != (b < 0));
    multiplicand = (a < 0) ? -(long long)a : (long long)a;
    multiplier = (b < 0) ? -(long long)b : (long long)b;
    limit = negative ? -(long long)INT_MIN : (long long)INT_MAX;

    while (multiplier > 0)
    {
        if ((multiplier & 1LL) != 0LL)
        {
            product += multiplicand;
            if (product > limit)
            {
                return false;
            }
        }
        multiplier >>= 1;
        multiplicand <<= 1;
    }

    *result = negative ? (int)(-product) : (int)product;
    return true;
}

int main(void)
{
    int a = -12;
    int b = 7;
    int result = 0;

    if (multiply_integers(a, b, &result))
    {
        printf("%d x %d = %d\n", a, b, result);
        return EXIT_SUCCESS;
    }

    printf("Error: multiplication overflow\n");
    return EXIT_FAILURE;
}