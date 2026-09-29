#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static long long centered_hexagonal(long long n)
{
    if (n < 1)
    {
        return -1;
    }
    if (n > 1000000000LL)
    {
        return -1;
    }
    return 3LL * n * (n - 1LL) + 1LL;
}

int main(void)
{
    long long n = 0;
    long long result = 0;

    if (scanf("%lld", &n) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = centered_hexagonal(n);
    if (result < 0)
    {
        fprintf(stderr, "Input out of range\n");
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", result) < 0)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}