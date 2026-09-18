#include <stdio.h>
#include <stdlib.h>

static long long count_sequences(long long m, long long n)
{
    long long total;
    long long k;

    if (n == 0) {
        return 1;
    }
    if (m <= 0) {
        return 0;
    }

    total = 0;
    for (k = 1; k <= m; k++) {
        total += count_sequences(k / 2, n - 1);
    }
    return total;
}

int main(void)
{
    long long m;
    long long n;
    long long result;

    if (scanf("%lld %lld", &m, &n) != 2) {
        fprintf(stderr, "Failed to read input values\n");
        return EXIT_FAILURE;
    }

    if (m < 0 || n < 0) {
        fprintf(stderr, "Invalid input values\n");
        return EXIT_FAILURE;
    }

    result = count_sequences(m, n);

    if (printf("Number of possible sequences: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}