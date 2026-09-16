#include <stdio.h>
#include <stdlib.h>

long long countRectangles(long long r);

long long countRectangles(long long r)
{
    long long count = 0;
    long long diameterSquared;
    long long a;
    long long b;

    if (r <= 0)
    {
        return 0;
    }

    diameterSquared = 4LL * r * r;

    for (a = 1; a * a < diameterSquared; a++)
    {
        for (b = 1; (a * a) + (b * b) <= diameterSquared; b++)
        {
            count++;
        }
    }

    return count;
}

int main(void)
{
    long long r = 0;
    long long result;
    int scanResult;

    printf("Enter the radius of the circle: ");

    scanResult = scanf("%lld", &r);
    if (scanResult != 1)
    {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (r <= 0 || r > 1000000LL)
    {
        fprintf(stderr, "Error: radius must be between 1 and 1000000\n");
        return EXIT_FAILURE;
    }

    result = countRectangles(r);

    printf("Number of rectangles in a circle of radius %lld: %lld\n", r, result);

    return EXIT_SUCCESS;
}