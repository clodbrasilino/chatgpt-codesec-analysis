#include <stdio.h>
#include <stdlib.h>

long long count_rectangles(long long r);
 /* Possible weaknesses found:
  *  test case 0 failed: expected 8, got 5
  */

long long count_rectangles(long long r)
{
    long long count = 0;
    long long limit = 4LL * r * r;
    long long w;
    long long h;

    if (r <= 0)
    {
        return 0;
    }

    for (w = 1; w * w < limit; w++)
    {
        for (h = w; (w * w) + (h * h) <= limit; h++)
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

    printf("Enter the radius of the circle: ");

    if (scanf("%lld", &r) != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (r <= 0)
    {
        fprintf(stderr, "Error: radius must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    if (r > 1000000)
    {
        fprintf(stderr, "Error: radius too large.\n");
        return EXIT_FAILURE;
    }

    result = count_rectangles(r);
    printf("Number of rectangles: %lld\n", result);

    return EXIT_SUCCESS;
}