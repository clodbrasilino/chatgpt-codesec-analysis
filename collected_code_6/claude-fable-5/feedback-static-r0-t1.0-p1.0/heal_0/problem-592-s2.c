#include <stdio.h>
#include <stdlib.h>

unsigned long long binomialCoeff(unsigned int n, unsigned int k)
{
    unsigned long long res = 1ULL;
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
        res = res * (unsigned long long)(n - i);
        res = res / (unsigned long long)(i + 1U);
    }

    return res;
}

unsigned long long sumOfProduct(unsigned int n)
{
    unsigned long long sum = 0ULL;
    unsigned int i;

    for (i = 0U; i < n; i++)
    {
        sum += binomialCoeff(n, i) * binomialCoeff(n, i + 1U);
    }

    return sum;
}

int main(void)
{
    unsigned int n;
    int scanResult;

    printf("Enter n (0 to 30): ");
    scanResult = scanf("%u", &n);

    if (scanResult != 1)
    {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (n > 30U)
    {
        fprintf(stderr, "Error: n must be between 0 and 30\n");
        return EXIT_FAILURE;
    }

    printf("Sum of product of binomial coefficients: %llu\n", sumOfProduct(n));

    return EXIT_SUCCESS;
}