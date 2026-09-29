#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
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
    unsigned int i = 1U;
    for (;;)
    {
        total += (unsigned long long)countUnsetBits(i);
        if (i == n)
        {
            break;
        }
        i++;
    }
    return total;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    unsigned int n = 0U;

    if (argc > 1)
    {
        char *end = NULL;
        unsigned long parsed;
        errno = 0;
        parsed = strtoul(argv[1], &end, 10);
        if (errno != 0 || end == argv[1] || *end != '\0' || parsed < 1UL || parsed > (unsigned long)UINT_MAX)
        {
            fprintf(stderr, "Error: invalid input\n");
            return EXIT_FAILURE;
        }
        n = (unsigned int)parsed;
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