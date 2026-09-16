#include <stdio.h>
#include <stdlib.h>

static unsigned long long binomial_coefficient(unsigned int n, unsigned int k)
{
    unsigned long long result = 1ULL;
    unsigned int i;

    if (k > n)
    {
        return 0ULL;
    }

    if (k > n - k)
    {
        k = n - k;
    }

    for (i = 0U; i < k; i++)
    {
        result = result * (unsigned long long)(n - i);
        result = result / (unsigned long long)(i + 1U);
    }

    return result;
}

static int lobb_number(unsigned int m, unsigned int n, unsigned long long *out)
{
    unsigned long long binom;

    if (out == NULL)
    {
        return -1;
    }

    if (m > n)
    {
        return -1;
    }

    if (n > 30U)
    {
        return -1;
    }

    binom = binomial_coefficient(2U * n, m + n);
    *out = ((2ULL * (unsigned long long)m + 1ULL) * binom) / ((unsigned long long)m + (unsigned long long)n + 1ULL);

    return 0;
}

int main(void)
{
    unsigned int m;
    unsigned int n;
    unsigned long long result;

    printf("Enter m: ");
    if (scanf("%u", &m) != 1)
    {
        fprintf(stderr, "Invalid input for m\n");
        return EXIT_FAILURE;
    }

    printf("Enter n: ");
    if (scanf("%u", &n) != 1)
    {
        fprintf(stderr, "Invalid input for n\n");
        return EXIT_FAILURE;
    }

    if (lobb_number(m, n, &result) != 0)
    {
        fprintf(stderr, "Invalid arguments: require m <= n and n <= 30\n");
        return EXIT_FAILURE;
    }

    printf("Lobb number L(%u, %u) = %llu\n", m, n, result);

    return EXIT_SUCCESS;
}