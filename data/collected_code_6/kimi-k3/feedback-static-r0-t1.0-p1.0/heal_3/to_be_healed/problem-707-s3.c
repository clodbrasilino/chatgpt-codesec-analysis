#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long countSetBits(unsigned int n)
{
    unsigned long long count = 0;
    unsigned int i;

    for (i = 1; i <= n; ++i)
    {
        count += (unsigned int)__builtin_popcount(i);
    }

    return count;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;
    long value;
    unsigned int n;
    unsigned long long result;
    size_t len;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = 0;
    while (len < sizeof(buffer) && buffer[len] != '\0')
    {
        ++len;
    }

    if (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n')
    {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtol(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || value < 1 || value > UINT_MAX)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    n = (unsigned int)value;
    result = countSetBits(n);

    printf("Total set bits from 1 to %u: %llu\n", n, result);

    return EXIT_SUCCESS;
}