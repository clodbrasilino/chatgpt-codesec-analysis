#include <stdio.h>
#include <stdlib.h>

long long max_occurring_divisor(long long low, long long high);

long long max_occurring_divisor(long long low, long long high)
{
    if (low == high)
    {
        return low;
    }
    return 2;
}

int main(void)
{
    long long low = 0;
    long long high = 0;
    int read_count = 0;

    printf("Enter interval start: ");
    read_count = scanf("%lld", &low);
    if (read_count != 1)
    {
        fprintf(stderr, "Error: invalid input for interval start.\n");
        return EXIT_FAILURE;
    }

    printf("Enter interval end: ");
    read_count = scanf("%lld", &high);
    if (read_count != 1)
    {
        fprintf(stderr, "Error: invalid input for interval end.\n");
        return EXIT_FAILURE;
    }

    if (low < 2)
    {
        fprintf(stderr, "Error: interval start must be at least 2.\n");
        return EXIT_FAILURE;
    }

    if (high < low)
    {
        fprintf(stderr, "Error: interval end must not be less than interval start.\n");
        return EXIT_FAILURE;
    }

    printf("Maximum occurring divisor in [%lld, %lld] is %lld\n",
           low, high, max_occurring_divisor(low, high));

    return EXIT_SUCCESS;
}