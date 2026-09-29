#include <stdio.h>
#include <stdlib.h>

static unsigned int count_set_bits(unsigned int num)
{
    unsigned int count = 0U;

    while (num > 0U)
    {
        count += (num & 1U);
        num >>= 1U;
    }

    return count;
}

static unsigned long long total_set_bits(unsigned int n)
{
    unsigned long long total = 0ULL;
    unsigned int i = 1U;

    for (;;)
    {
        total += (unsigned long long)count_set_bits(i);

        if (i == n)
        {
            break;
        }

        i++;
    }

    return total;
}

int main(void)
{
    unsigned int n = 0U;
    int result;

    printf("Enter a positive integer n: ");

    result = scanf("%u", &n);
    if (result != 1)
    {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (n == 0U)
    {
        fprintf(stderr, "Error: n must be greater than 0\n");
        return EXIT_FAILURE;
    }

    printf("Total set bits from 1 to %u: %llu\n", n, total_set_bits(n));

    return EXIT_SUCCESS;
}