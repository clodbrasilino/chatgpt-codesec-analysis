#include <stdio.h>
#include <stdlib.h>

static unsigned long long binomial_coefficient(int n, int k)
{
    unsigned long long result;
    int i;

    if (k < 0 || k > n) {
        return 0ULL;
    }

    if (k > n - k) {
        k = n - k;
    }

    result = 1ULL;
    for (i = 0; i < k; i++) {
        result = result * (unsigned long long)(n - i);
        result = result / (unsigned long long)(i + 1);
    }

    return result;
}

static int lobb_number(int n, int m, unsigned long long *out)
{
    unsigned long long binom;

    if (out == NULL || n < 0 || m < 0 || m > n) {
        return -1;
    }

    binom = binomial_coefficient(2 * n, m + n);
    *out = ((unsigned long long)(2 * m + 1) * binom) / (unsigned long long)(m + n + 1);

    return 0;
}

int main(void)
{
    int n;
    int m;
    unsigned long long result;

    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input for n\n");
        return EXIT_FAILURE;
    }

    printf("Enter m: ");
    if (scanf("%d", &m) != 1) {
        fprintf(stderr, "Invalid input for m\n");
        return EXIT_FAILURE;
    }

    if (n < 0 || n > 30 || m < 0 || m > n) {
        fprintf(stderr, "Constraints: 0 <= m <= n <= 30\n");
        return EXIT_FAILURE;
    }

    if (lobb_number(n, m, &result) != 0) {
        fprintf(stderr, "Failed to compute Lobb number\n");
        return EXIT_FAILURE;
    }

    printf("Lobb number L(%d, %d) = %llu\n", m, n, result);

    return EXIT_SUCCESS;
}