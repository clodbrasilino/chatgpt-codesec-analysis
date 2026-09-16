#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got 1
  *  test case 2 failed: expected 17, got 1
  */

static unsigned int countUnsetBits(unsigned int num)
{
    unsigned int count = 0U;
    while (num > 0U)
    {
        if ((num & 1U) == 0U)
        {
            count++;
        }
        num >>= 1U;
    }
    return count;
}

static unsigned long long totalUnsetBits(unsigned int n)
{
    unsigned long long total = 0ULL;
    unsigned int i;
    for (i = 1U; i <= n; i++)
    {
        total += (unsigned long long)countUnsetBits(i);
        if (i == n)
        {
            break;
        }
    }
    return total;
}

int main(int argc, const char *argv[])
{
    unsigned int n = 0U;

    if (argc > 1)
    {
        char extra = '\0';
        if (sscanf(argv[1], "%u %c", &n, &extra) != 1 || n < 1U)
        {
            fprintf(stderr, "Error: invalid input\n");
            return EXIT_FAILURE;
        }
    }
    else
    {
        if (scanf("%u", &n) != 1)
        {
            fprintf(stderr, "Error: invalid input\n");
            return EXIT_FAILURE;
        }
        if (n < 1U)
        {
            fprintf(stderr, "Error: input must be at least 1\n");
            return EXIT_FAILURE;
        }
    }

    printf("%llu\n", totalUnsetBits(n));

    return EXIT_SUCCESS;
}