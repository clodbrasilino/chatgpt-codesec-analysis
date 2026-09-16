#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int cmpAsc(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

static long long pow2MinusOne(int e) {
    if (e < 0) return -1;
    if (e == 0) return 0;
    if (e >= 64) return -1;
    unsigned long long val = 1ULL << e;
    return (long long)(val - 1);
}

static long long countPositiveRec(const int *arr, int n, int k, int idx, long long current) {
    if (idx >= n) return 0;

    int r = n - idx;
    long long full = current;
    int allValid = 1;

    for (int i = idx; i < n; ++i) {
        if (arr[i] > (k - 1) / full) {
            allValid = 0;
            break;
        }
        full *= arr[i];
    }

    if (allValid) {
        return pow2MinusOne(r);
    }

    long long count = 0;
    for (int i = idx; i < n; ++i) {
        if (arr[i] > (k - 1) / current) break;

        long long sub = countPositiveRec(arr, n, k, i + 1, current * arr[i]);
        if (sub < 0 || count > LLONG_MAX - sub - 1) return -1;

        count += 1 + sub;
    }

    return count;
}

static long long countPositiveSubsets(int *arr, int n, int k) {
    if (n <= 0 || k <= 0) return 0;

    qsort(arr, n, sizeof(int), cmpAsc);
    return countPositiveRec(arr, n, k, 0, 1);
}

long long countSubsequencesProductLessThanK(const int arr[], int n, int k) {
    if (n < 0) return -1;
    if (n == 0 || k <= 0) return 0;
    if (arr == NULL) return -1;

    int z = 0;
    int m = 0;

    for (int i = 0; i < n; ++i) {
        if (arr[i] == 0) z++;
        else if (arr[i] > 0) m++;
    }

    long long posCount = 0;

    if (m > 0) {
        int *pos = (int *)calloc((size_t)m, sizeof(int));
        if (pos == NULL) return -1;

        int idx = 0;
        for (int i = 0; i < n; ++i) {
            if (arr[i] > 0) pos[idx++] = arr[i];
        }

        posCount = countPositiveSubsets(pos, m, k);
        free(pos);

        if (posCount < 0) return -1;
    }

    if (z == 0) return posCount;

    long long zeroSubsets = pow2MinusOne(z);
    if (zeroSubsets < 0) return -1;

    if (m >= 63) return -1;

    long long p2m = 1LL << m;

    if (zeroSubsets != 0 && p2m > LLONG_MAX / zeroSubsets) return -1;

    long long zeroContaining = p2m * zeroSubsets;

    if (posCount > LLONG_MAX - zeroContaining) return -1;

    return posCount + zeroContaining;
}

int main(void) {
    int arr[] = {0, 1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 4;

    printf("%lld\n", countSubsequencesProductLessThanK(arr, n, k));
    return 0;
}