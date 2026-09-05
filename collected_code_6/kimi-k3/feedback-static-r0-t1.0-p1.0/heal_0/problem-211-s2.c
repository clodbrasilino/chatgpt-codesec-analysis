#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int count_numbers_with_bits_set(unsigned int start, unsigned int end, unsigned int o, unsigned int n, unsigned int *count)
{
    unsigned int i;
    unsigned int mask;
    unsigned int cnt;

    if (count == NULL)
    {
        return -1;
    }

    if (o >= (sizeof(unsigned int) * CHAR_BIT) || n >= (sizeof(unsigned int) * CHAR_BIT))
    {
        return -2;
    }

    if (start > end)
    {
        return -3;
    }

    mask = (1U << o) | (1U << n);
    cnt = 0U;

    for (i = start; i <= end; i++)
    {
        if ((i & mask) == mask)
        {
            cnt++;
        }

        if (i == UINT_MAX)
        {
            break;
        }
    }

    *count = cnt;
    return 0;
}

int main(void)
{
    unsigned int count;
    int result;

    result = count_numbers_with_bits_set(0U, 100U, 2U, 3U, &count);
    if (result == 0)
    {
        printf("Count: %u\n", count);
    }
    else
    {
        printf("Error: %d\n", result);
    }

    return 0;
}