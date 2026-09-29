#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long permutation(int n, int k)
{
    unsigned long long result;
    int i;

    if (n < 0 || k < 0 || k > n) {
        return 0ULL;
    }

    result = 1ULL;

    for (i = 0; i < k; ++i) {
        if (result > ULLONG_MAX / (unsigned long long)(n - i)) {
            return 0ULL;
        }
        result *= (unsigned long long)(n - i);
    }

    return result;
}

int main(void)
{
    int n;
    int k;
    unsigned long long result;

    if (printf("Enter n and k: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%d %d", &n, &k) != 2) {
        (void)fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0 || k < 0 || k > n) {
        (void)fprintf(stderr, "Invalid values: require 0 <= k <= n\n");
        return EXIT_FAILURE;
    }

    result = permutation(n, k);

    if (result == 0ULL && !(n == 0 && k == 0) && !(k == 0)) {
        (void)fprintf(stderr, "Overflow occurred or invalid input\n");
        return EXIT_FAILURE;
    }

    if (printf("P(%d, %d) = %llu\n", n, k, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}