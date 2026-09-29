#include <stdio.h>
#include <stdlib.h>

static unsigned long long binomial(unsigned int n, unsigned int k)
{
    unsigned long long result = 1ULL;
    unsigned int i;

    if (k > n) {
        return 0ULL;
    }
    if (k > n - k) {
        k = n - k;
    }
    for (i = 0U; i < k; i++) {
        result = result * (unsigned long long)(n - i);
        result = result / (unsigned long long)(i + 1U);
    }
    return result;
}

static unsigned long long derangement(unsigned int n)
{
    unsigned long long prev2 = 1ULL;
    unsigned long long prev1 = 0ULL;
    unsigned long long current;
    unsigned int i;

    if (n == 0U) {
        return 1ULL;
    }
    if (n == 1U) {
        return 0ULL;
    }
    current = 0ULL;
    for (i = 2U; i <= n; i++) {
        current = (unsigned long long)(i - 1U) * (prev1 + prev2);
        prev2 = prev1;
        prev1 = current;
    }
    return current;
}

static int rencontres_number(unsigned int n, unsigned int k, unsigned long long *out)
{
    if (out == NULL) {
        return -1;
    }
    if (k > n) {
        return -1;
    }
    if (n > 20U) {
        return -1;
    }
    *out = binomial(n, k) * derangement(n - k);
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
        return EXIT_FAILURE;
    }

    printf("Enter k: ");
    if (scanf("%u", &k) != 1) {
        fprintf(stderr, "Invalid input for k\n");
        return EXIT_FAILURE;
    }

    status = rencontres_number(n, k, &result);
    if (status != 0) {
        fprintf(stderr, "Invalid arguments: require k <= n and n <= 20\n");
        return EXIT_FAILURE;
    }

    printf("Rencontres number D(%u, %u) = %llu\n", n, k, result);
    return EXIT_SUCCESS;
}