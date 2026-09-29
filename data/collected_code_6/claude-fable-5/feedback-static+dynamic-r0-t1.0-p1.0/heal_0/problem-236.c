#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static long long count_triangles(long long n)
{
    long long result;

    if (n < 0)
    {
        return -1LL;
    }

    if (n > 1000000LL)
    {
        return -1LL;
    }

    result = (n * (n + 2LL) * (2LL * n + 1LL)) / 8LL;

    return result;
}

int main(void)
{
    long long n;
    long long total;
    int scanned;

    printf("Enter the side length of the equilateral triangle: ");

    scanned = scanf("%lld", &n);

    if (scanned != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    total = count_triangles(n);

    if (total < 0LL)
    {
        fprintf(stderr, "Error: input out of supported range.\n");
        return EXIT_FAILURE;
    }

    printf("Maximum number of equilateral triangles: %lld\n", total);

    return EXIT_SUCCESS;
}