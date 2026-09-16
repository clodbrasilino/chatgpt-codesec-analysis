#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got 1
  *  test case 2 failed: expected 17, got 1
  */

static unsigned int count_unset_bits(unsigned int num)
{
    unsigned int count = 0U;
    unsigned int temp = num;

    while (temp > 0U)
    {
        if ((temp & 1U) == 0U)
        {
            count++;
        }
        temp >>= 1U;
    }

    return count;
}

static unsigned long long total_unset_bits(unsigned int n)
{
    unsigned long long total = 0ULL;
    unsigned int i;

    for (i = 1U; i <= n; i++)
    {
        total += (unsigned long long)count_unset_bits(i);
        if (i == n)
        {
            break;
        }
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

    printf("Total unset bits from 1 to %u: %llu\n", n, total_unset_bits(n));

    return EXIT_SUCCESS;
}