#include <stdio.h>
#include <stdlib.h>

static unsigned long long binomialCoeff(unsigned int n, unsigned int k)
{
    unsigned long long res = 1ULL;
    unsigned int i;

    if (k > n) {
        return 0ULL;
    }
    if (k > (n - k)) {
        k = n - k;
    }
    for (i = 0U; i < k; i++) {
        res = (res * (unsigned long long)(n - i)) / (unsigned long long)(i + 1U);
    }
    return res;
}

static int sumOfProductOfBinomials(unsigned int n, unsigned long long *result)
{
    if (result == NULL) {
        return -1;
    }
    if (n > 31U) {
        return -1;
    }
    if (n == 0U) {
        *result = 0ULL;
        return 0;
    }
    *result = binomialCoeff(2U * n, n - 1U);
    return 0;
}

int main(void)
{
    unsigned int n = 0U;
    unsigned long long answer = 0ULL;
    int scanResult;

    printf("Enter n (0 to 31): ");
    scanResult = scanf("%u", &n);
    if (scanResult != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (sumOfProductOfBinomials(n, &answer) != 0) {
        fprintf(stderr, "Error: n out of supported range.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of product of binomial coefficients for n = %u is %llu\n", n, answer);
    return EXIT_SUCCESS;
}