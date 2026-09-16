#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool allBitsUnsetInRange(unsigned int num, unsigned int left, unsigned int right, bool *result)
{
    unsigned int mask;

    if (result == NULL)
    {
        return false;
    }

    if (left < 1U || right < 1U || left > 32U || right > 32U || left > right)
    {
        return false;
    }

    if (right == 32U)
    {
        mask = ~0U;
    }
    else
    {
        mask = (1U << right) - 1U;
    }

    mask &= ~((1U << (left - 1U)) - 1U);

    *result = ((num & mask) == 0U);

    return true;
}

int main(void)
{
    unsigned int num = 17U;
    unsigned int left = 2U;
    unsigned int right = 4U;
    bool result = false;

    if (!allBitsUnsetInRange(num, left, right, &result))
    {
        if (fprintf(stderr, "Invalid range provided\n") < 0)
        {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (result)
    {
        if (printf("All bits are unset in the range [%u, %u] of %u\n", left, right, num) < 0)
        {
            return EXIT_FAILURE;
        }
    }
    else
    {
        if (printf("Not all bits are unset in the range [%u, %u] of %u\n", left, right, num) < 0)
        {
            return EXIT_FAILURE;
        }
    }

    num = 16U;
    if (!allBitsUnsetInRange(num, left, right, &result))
    {
        if (fprintf(stderr, "Invalid range provided\n") < 0)
        {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (result)
    {
        if (printf("All bits are unset in the range [%u, %u] of %u\n", left, right, num) < 0)
        {
            return EXIT_FAILURE;
        }
    }
    else
    {
        if (printf("Not all bits are unset in the range [%u, %u] of %u\n", left, right, num) < 0)
        {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}