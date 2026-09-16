#include <stdio.h>
#include <limits.h>

int binomial_coefficient(unsigned int n, unsigned int k, unsigned long long *result)
{
    unsigned long long res;
    unsigned int i;

    if (result == NULL) {
        return -1;
    }

    if (k > n) {
        *result = 0ULL;
        return 0;
    }

    if (k > n - k) {
        k = n - k;
    }

    res = 1ULL;
    for (i = 0U; i < k; i++) {
        unsigned long long numerator = (unsigned long long)(n - i);

        if (res > ULLONG_MAX / numerator) {
            return -2;
        }
        res *= numerator;
        res /= (unsigned long long)(i + 1U);
    }

    *result = res;
    return 0;
}

int main(void)
{
    unsigned int n;
    unsigned int k;
    unsigned long long result;
    int status;

    printf("Enter n: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input for n\n");
        return 1;
    }

    printf("Enter k: ");
    if (scanf("%u", &k) != 1) {
        fprintf(stderr, "Invalid input for k\n");
        return 1;
    }

    status = binomial_coefficient(n, k, &result);
    if (status == -2) {
        fprintf(stderr, "Result overflows unsigned long long\n");
        return 1;
    }
    if (status != 0) {
        fprintf(stderr, "Computation error\n");
        return 1;
    }

    printf("C(%u, %u) = %llu\n", n, k, result);
    return 0;
}