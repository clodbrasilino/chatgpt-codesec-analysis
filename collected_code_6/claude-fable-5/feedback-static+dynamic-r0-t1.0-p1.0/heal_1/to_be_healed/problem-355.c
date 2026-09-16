#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 8, got 5
  */

static long long count_rectangles(long long r)
{
    long long limit;
    long long count = 0;
    long long a;
    long long b;

    if (r <= 0)
    {
        return 0;
    }

    limit = 4LL * r * r;

    for (a = 1; a * a < limit; a++)
    {
        for (b = a; (a * a) + (b * b) <= limit; b++)
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
    int scan_result;

    printf("Enter the radius of the circle: ");

    scan_result = scanf("%lld", &r);
    if (scan_result != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (r <= 0)
    {
        fprintf(stderr, "Error: radius must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    if (r > 1000000LL)
    {
        fprintf(stderr, "Error: radius too large.\n");
        return EXIT_FAILURE;
    }

    result = count_rectangles(r);

    printf("Number of rectangles with integer sides that fit in a circle of radius %lld: %lld\n", r, result);

    return EXIT_SUCCESS;
}