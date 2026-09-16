#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

static unsigned long long satAdd(unsigned long long a, unsigned long long b)
{
    if (ULLONG_MAX - a < b) {
        return ULLONG_MAX;
    }
    return a + b;
}

static unsigned long long satDouble(unsigned long long a)
{
    return satAdd(a, a);
}

unsigned long long countSubsequencesWithProductLessThanK(const int *arr, size_t n, long long k)
{
    unsigned long long *dp;
    unsigned long long zeroFreeSubsets;
    unsigned long long zeroProductCount;
    unsigned long long positiveCount;
    size_t i;
    long long j;

    if (k <= 0LL || n == 0 || arr == NULL) {
        return 0ULL;
    }

    if ((unsigned long long)k > (unsigned long long)(SIZE_MAX / sizeof(unsigned long long))) {
        return 0ULL;
    }

    dp = (unsigned long long *)calloc((size_t)k, sizeof(unsigned long long));
    if (dp == NULL) {
        return 0ULL;
    }

    zeroFreeSubsets = 1ULL;
    zeroProductCount = 0ULL;

    for (i = 0; i < n; i++) {
        long long value = (long long)arr[i];
        if (value < 0LL) {
            free(dp);
            return 0ULL;
        }
        if (value == 0LL) {
            zeroProductCount = satAdd(satDouble(zeroProductCount), zeroFreeSubsets);
        } else {
            zeroProductCount = satDouble(zeroProductCount);
            zeroFreeSubsets = satDouble(zeroFreeSubsets);
            for (j = k - 1LL; j >= 1LL; j--) {
                if (dp[j] != 0ULL && value <= (k - 1LL) / j) {
                    dp[j * value] = satAdd(dp[j * value], dp[j]);
                }
            }
            if (value < k) {
                dp[value] = satAdd(dp[value], 1ULL);
            }
        }
    }

    positiveCount = 0ULL;
    for (j = 1LL; j < k; j++) {
        positiveCount = satAdd(positiveCount, dp[j]);
    }

    free(dp);
    dp = NULL;

    return satAdd(zeroProductCount, positiveCount);
}

int main(void)
{
    int n;
    int i;
    int *arr;
    long long k;
    unsigned long long result;

    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    arr = NULL;
    if (n > 0) {
        arr = (int *)malloc((size_t)n * sizeof(int));
        if (arr == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
    }

    if (scanf("%lld", &k) != 1) {
        fprintf(stderr, "Invalid input\n");
        free(arr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1 || arr[i] < 0) {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }

    result = countSubsequencesWithProductLessThanK(arr, (size_t)n, k);
    printf("%llu\n", result);

    free(arr);
    arr = NULL;

    return EXIT_SUCCESS;
}