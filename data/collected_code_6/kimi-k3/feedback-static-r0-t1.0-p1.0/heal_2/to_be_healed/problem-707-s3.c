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
    char buffer[32];
    char *endptr;
    long value;
    unsigned int n;
    unsigned long long result;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
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