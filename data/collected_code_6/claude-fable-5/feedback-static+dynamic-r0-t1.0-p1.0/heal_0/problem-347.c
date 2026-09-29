#include <stdio.h>
#include <stdlib.h>

static long long count_squares(long long m, long long n)
{
    long long total = 0;
    long long limit = (m < n) ? m : n;
    long long k;

    for (k = 1; k <= limit; k++) {
        total += (m - k + 1) * (n - k + 1);
    }

    return total;
}

int main(void)
{
    long long m;
    long long n;
    long long result;

    printf("Enter rectangle dimensions (m n): ");
    if (scanf("%lld %lld", &m, &n) != 2) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (m <= 0 || n <= 0) {
        fprintf(stderr, "Error: dimensions must be positive\n");
        return EXIT_FAILURE;
    }

    if (m > 100000 || n > 100000) {
        fprintf(stderr, "Error: dimensions too large\n");
        return EXIT_FAILURE;
    }

    result = count_squares(m, n);
    printf("Number of squares in a %lldx%lld rectangle: %lld\n", m, n, result);

    return EXIT_SUCCESS;
}