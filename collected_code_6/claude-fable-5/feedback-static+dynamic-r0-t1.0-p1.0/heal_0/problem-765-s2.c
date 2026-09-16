#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int is_power_of_two(unsigned long x)
{
    return (x != 0UL) && ((x & (x - 1UL)) == 0UL);
}

static unsigned long nth_polite(unsigned long n)
{
    unsigned long count = 0UL;
    unsigned long num = 2UL;

    while (num < ULONG_MAX)
    {
        if (!is_power_of_two(num))
        {
            count++;
            if (count == n)
            {
                return num;
            }
        }
        num++;
    }
    return 0UL;
}

int main(void)
{
    unsigned long n = 0UL;
    unsigned long result = 0UL;

    printf("Enter n: ");
    if (scanf("%lu", &n) != 1)
    {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (n == 0UL)
    {
        fprintf(stderr, "Error: n must be at least 1\n");
        return EXIT_FAILURE;
    }

    result = nth_polite(n);
    if (result == 0UL)
    {
        fprintf(stderr, "Error: result out of range\n");
        return EXIT_FAILURE;
    }

    printf("The %lu-th polite number is %lu\n", n, result);
    return EXIT_SUCCESS;
}