#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct
{
    int value;
    bool ok;
} MultiplyResult;

static MultiplyResult multiply_ints(int a, int b)
{
    MultiplyResult res;
    unsigned int ua;
    unsigned int ub;
    unsigned int product;
    unsigned int limit;
    bool negative;

    res.value = 0;
    res.ok = false;

    negative = ((a < 0) != (b < 0));

    ua = (a < 0) ? (0u - (unsigned int)a) : (unsigned int)a;
    ub = (b < 0) ? (0u - (unsigned int)b) : (unsigned int)b;

    limit = negative ? ((unsigned int)INT_MAX + 1u) : (unsigned int)INT_MAX;

    product = 0u;
    while (ub != 0u)
    {
        if ((ub & 1u) != 0u)
        {
            if (ua > limit - product)
            {
                return res;
            }
            product += ua;
        }
        ub >>= 1;
        if (ub != 0u)
        {
            if (ua > limit - ua)
            {
                return res;
            }
            ua += ua;
        }
    }

    if (negative)
    {
        if (product == (unsigned int)INT_MAX + 1u)
        {
            res.value = INT_MIN;
        }
        else
        {
            res.value = -(int)product;
        }
    }
    else
    {
        res.value = (int)product;
    }

    res.ok = true;
    return res;
}

int main(void)
{
    int a;
    int b;
    MultiplyResult res;

    printf("Enter two integers: ");

    if (scanf("%d %d", &a, &b) != 2)
    {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    res = multiply_ints(a, b);

    if (!res.ok)
    {
        fprintf(stderr, "Error: multiplication overflow\n");
        return EXIT_FAILURE;
    }

    printf("Result: %d\n", res.value);

    return EXIT_SUCCESS;
}