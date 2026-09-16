#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

bool allBitsUnsetInRange(unsigned int n, unsigned int l, unsigned int r)
{
    unsigned int mask;
    unsigned int width;

    if (l < 1U || r < l || r > (unsigned int)(sizeof(unsigned int) * CHAR_BIT))
    {
        fprintf(stderr, "Invalid bit range: l=%u, r=%u\n", l, r);
        exit(EXIT_FAILURE);
    }

    width = r - l + 1U;

    if (width >= (unsigned int)(sizeof(unsigned int) * CHAR_BIT))
    {
        mask = ~0U;
    }
    else
    {
        mask = ((1U << width) - 1U) << (l - 1U);
    }

    return (n & mask) == 0U;
}

int main(void)
{
    unsigned int n = 17U;
    unsigned int l = 2U;
    unsigned int r = 4U;

    if (allBitsUnsetInRange(n, l, r))
    {
        printf("Yes, all bits from %u to %u are unset in %u\n", l, r, n);
    }
    else
    {
        printf("No, not all bits from %u to %u are unset in %u\n", l, r, n);
    }

    n = 39U;
    l = 4U;
    r = 5U;

    if (allBitsUnsetInRange(n, l, r))
    {
        printf("Yes, all bits from %u to %u are unset in %u\n", l, r, n);
    }
    else
    {
        printf("No, not all bits from %u to %u are unset in %u\n", l, r, n);
    }

    return EXIT_SUCCESS;
}