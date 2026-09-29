#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static long long count_triangles(int n)
{
    long long ln;

    if (n < 0)
    {
        return -1LL;
    }

    ln = (long long)n;
    return (ln * (ln + 2LL) * (2LL * ln + 1LL)) / 8LL;
}

int main(void)
{
    int n = 0;
    long long result;

    printf("Enter the side length of the equilateral triangle: ");

    if (scanf("%d", &n) != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n < 0 || n > 100000)
    {
        fprintf(stderr, "Error: input out of valid range (0 to 100000).\n");
        return EXIT_FAILURE;
    }

    result = count_triangles(n);

    if (result < 0)
    {
        fprintf(stderr, "Error: computation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Maximum number of equilateral triangles: %lld\n", result);

    return EXIT_SUCCESS;
}