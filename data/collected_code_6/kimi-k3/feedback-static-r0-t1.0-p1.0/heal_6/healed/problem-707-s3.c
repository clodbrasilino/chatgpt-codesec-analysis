#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

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
    char buffer[128];
    char *endptr;
    long value;
    unsigned int n;
    unsigned long long result;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(buffer, sizeof(buffer));

    if (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n')
    {
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