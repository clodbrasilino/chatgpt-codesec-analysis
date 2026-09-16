#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int is_perfect_square(long long num)
{
    long long root;

    if (num < 0)
    {
        return 0;
    }

    root = (long long)llround(sqrt((double)num));

    if (root * root == num)
    {
        return 1;
    }

    if ((root + 1) * (root + 1) == num)
    {
        return 1;
    }

    if (root > 0 && (root - 1) * (root - 1) == num)
    {
        return 1;
    }

    return 0;
}

int find_perfect_squares(long long low, long long high)
{
    long long i;
    int count = 0;

    if (low > high)
    {
        long long temp = low;
        low = high;
        high = temp;
    }

    for (i = low; i <= high; i++)
    {
        if (is_perfect_square(i))
        {
            if (printf("%lld\n", i) < 0)
            {
                return -1;
            }
            count++;
        }
        if (i == high)
        {
            break;
        }
    }

    return count;
}

int main(void)
{
    long long low;
    long long high;
    int result;

    if (printf("Enter the lower bound: ") < 0)
    {
        return EXIT_FAILURE;
    }

    if (scanf("%lld", &low) != 1)
    {
        fprintf(stderr, "Invalid input for lower bound\n");
        return EXIT_FAILURE;
    }

    if (printf("Enter the upper bound: ") < 0)
    {
        return EXIT_FAILURE;
    }

    if (scanf("%lld", &high) != 1)
    {
        fprintf(stderr, "Invalid input for upper bound\n");
        return EXIT_FAILURE;
    }

    result = find_perfect_squares(low, high);

    if (result < 0)
    {
        fprintf(stderr, "Output error occurred\n");
        return EXIT_FAILURE;
    }

    if (printf("Total perfect squares found: %d\n", result) < 0)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}