#include <stdio.h>
#include <stdlib.h>

static long long count_sequences(long long m, long long n)
{
    if (n == 0)
    {
        return 1;
    }
    if (m <= 0)
    {
        return 0;
    }
    return count_sequences(m - 1, n) + count_sequences(m / 2, n - 1);
}

int main(void)
{
    long long m;
    long long n;

    printf("Enter m: ");
    if (scanf("%lld", &m) != 1)
    {
        fprintf(stderr, "Invalid input for m\n");
        return EXIT_FAILURE;
    }

    printf("Enter n: ");
    if (scanf("%lld", &n) != 1)
    {
        fprintf(stderr, "Invalid input for n\n");
        return EXIT_FAILURE;
    }

    if (m < 0 || n < 0)
    {
        fprintf(stderr, "Values must be non-negative\n");
        return EXIT_FAILURE;
    }

    if (n > 62 || m > 1000000)
    {
        fprintf(stderr, "Input values too large\n");
        return EXIT_FAILURE;
    }

    printf("Number of possible sequences: %lld\n", count_sequences(m, n));

    return EXIT_SUCCESS;
}