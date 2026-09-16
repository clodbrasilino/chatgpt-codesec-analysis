#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long countTriangles(int n);

long long countTriangles(int n)
{
    long long size;
    long long result;

    if (n < 0)
    {
        return -1;
    }

    size = (long long)n;
    result = (size * (size + 2LL) * (2LL * size + 1LL)) / 8LL;

    return result;
}

int main(void)
{
    int n;
    int scanResult;
    long long total;

    printf("Enter the side length of the equilateral triangle: ");

    scanResult = scanf("%d", &n);
    if (scanResult != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n < 0 || n > 100000)
    {
        fprintf(stderr, "Error: side length must be between 0 and 100000.\n");
        return EXIT_FAILURE;
    }

    total = countTriangles(n);
    if (total < 0)
    {
        fprintf(stderr, "Error: computation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Maximum number of equilateral triangles: %lld\n", total);

    return EXIT_SUCCESS;
}