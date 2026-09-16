#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int cmp(const void *a, const void *b) {
    unsigned long long va = *(const unsigned long long *)a;
    unsigned long long vb = *(const unsigned long long *)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

unsigned long long safe_add(unsigned long long a, unsigned long long b) {
    if (a > ULLONG_MAX - b) return ULLONG_MAX;
    return a + b;
}

unsigned long long safe_mul(unsigned long long a, unsigned long long b) {
    if (a > 0 && b > ULLONG_MAX / a) return ULLONG_MAX;
    return a * b;
}

unsigned long long safe_pow2(size_t exp) {
    if (exp >= 64) return ULLONG_MAX;
    return 1ULL << exp;
}

unsigned long long count_subsequences(int *arr, size_t n, unsigned long long k) {
    unsigned long long count = 0;
    unsigned long long *pos_arr = NULL;
    size_t p = 0;
    size_t z = 0;

    if (arr == NULL && n > 0) {
        return ULLONG_MAX;
    }

    if (n == 0) {
        return 0;
    }

    pos_arr = (unsigned long long *)malloc(n * sizeof(unsigned long long));
    if (pos_arr == NULL) {
        return ULLONG_MAX;
    }

    for (size_t i = 0; i < n; i++) {
        if (arr[i] == 0) {
            z++;
        } else if (arr[i] > 0) {
            pos_arr[p++] = (unsigned long long)arr[i];
        }
    }

    if (k == 0) {
        free(pos_arr);
        return 0;
    }

    qsort(pos_arr, p, sizeof(unsigned long long), cmp);

    unsigned long long pos_count = 0;
    long double log_prod = 0.0L;
    long double log_k = logl((long double)k);
    size_t left = 0;

    for (size_t right = 0; right < p; right++) {
        log_prod += logl((long double)pos_arr[right]);
        while (left <= right && log_prod >= log_k) {
            log_prod -= logl((long double)pos_arr[left]);
            left++;
        }
        size_t diff = right - left;
        unsigned long long p_pow = safe_pow2(diff);
        pos_count = safe_add(pos_count, p_pow);
        if (pos_count == ULLONG_MAX) {
            free(pos_arr);
            return ULLONG_MAX;
        }
    }

    unsigned long long z_pow = safe_pow2(z);
    unsigned long long z_part = (z_pow == ULLONG_MAX) ? ULLONG_MAX : z_pow - 1;
    unsigned long long p_total = safe_pow2(p);
    unsigned long long zeros_count = safe_mul(z_part, p_total);

    count = safe_add(pos_count, zeros_count);

    free(pos_arr);
    return count;
}

int main(void) {
    int arr1[] = {0, 1, 2, 3};
    unsigned long long k1 = 4;
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    unsigned long long res1 = count_subsequences(arr1, n1, k1);
    printf("%llu\n", res1);

    int arr2[] = {2, 3, 4};
    unsigned long long k2 = 10;
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    unsigned long long res2 = count_subsequences(arr2, n2, k2);
    printf("%llu\n", res2);

    return 0;
}