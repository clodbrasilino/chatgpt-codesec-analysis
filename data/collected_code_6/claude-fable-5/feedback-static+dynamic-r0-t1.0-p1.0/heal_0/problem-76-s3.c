#include <stdio.h>
#include <stdlib.h>

static long long count_squares(long long m, long long n)
{
    long long total = 0;
    long long limit = (m < n) ? m : n;
    long long i;

    for (i = 1; i <= limit; i++) {
        total += (m - i + 1) * (n - i + 1);
    }

    return total;
}

int main(void)
{
    long long m;
    long long n;

    printf("Enter rectangle dimensions (m n): ");

    if (scanf("%lld %lld", &m, &n) != 2) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (m <= 0 || n <= 0) {
        fprintf(stderr, "Error: dimensions must be positive\n");
        return EXIT_FAILURE;
    }

    if (m > 1000000 || n > 1000000) {
        fprintf(stderr, "Error: dimensions too large\n");
        return EXIT_FAILURE;
    }

    printf("Number of squares: %lld\n", count_squares(m, n));

    return EXIT_SUCCESS;
}