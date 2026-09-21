#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#define MOD 1000000007LL
#define MAX_RANGE 1000000LL

static int compare_ll(const void *a, const void *b) {
    long long x = *(const long long *)a;
    long long y = *(const long long *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

static int check_mul_overflow_ll(long long a, long long b, long long *result) {
    if (a == 0 || b == 0) {
        *result = 0;
        return 0;
    }
    if (a > 0) {
        if (b > 0) {
            if (a > LLONG_MAX / b) return -1;
        } else {
            if (b < LLONG_MIN / a) return -1;
        }
    } else {
        if (b > 0) {
            if (a < LLONG_MIN / b) return -1;
        } else {
            if (a < LLONG_MAX / b) return -1;
        }
    }
    *result = a * b;
    return 0;
}

static int check_add_overflow_ll(long long a, long long b, long long *result) {
    if (b > 0 && a > LLONG_MAX - b) return -1;
    if (b < 0 && a < LLONG_MIN - b) return -1;
    *result = a + b;
    return 0;
}

static int check_sub_overflow_ll(long long a, long long b, long long *result) {
    if (b < 0 && a > LLONG_MAX + b) return -1;
    if (b > 0 && a < LLONG_MIN + b) return -1;
    *result = a - b;
    return 0;
}

long long count_sequences(int n, const long long *values, int num_values) {
    if (n < 0 || num_values <= 0 || values == NULL) {
        return 0;
    }

    if ((size_t)num_values > SIZE_MAX / sizeof(long long)) {
        return 0;
    }

    size_t copy_size = (size_t)num_values * sizeof(long long);

    long long *sorted = (long long *)malloc(copy_size);
    if (sorted == NULL) {
        return 0;
    }

    memcpy(sorted, values, copy_size);

    qsort(sorted, (size_t)num_values, sizeof(long long), compare_ll);

    long long max_pos = 0;
    long long min_neg = 0;
    for (int i = 0; i < num_values; i++) {
        if (sorted[i] > max_pos) max_pos = sorted[i];
        if (sorted[i] < min_neg) min_neg = sorted[i];
    }

    long long max_sum, min_sum;
    if (check_mul_overflow_ll(max_pos, (long long)n, &max_sum) != 0) {
        free(sorted);
        return 0;
    }
    if (check_mul_overflow_ll(min_neg, (long long)n, &min_sum) != 0) {
        free(sorted);
        return 0;
    }

    long long range;
    if (check_sub_overflow_ll(max_sum, min_sum, &range) != 0) {
        free(sorted);
        return 0;
    }
    if (check_add_overflow_ll(range, 1, &range) != 0) {
        free(sorted);
        return 0;
    }

    if (range <= 0 || range > MAX_RANGE) {
        free(sorted);
        return 0;
    }

    long long offset_ll;
    if (check_sub_overflow_ll(0, min_sum, &offset_ll) != 0) {
        free(sorted);
        return 0;
    }

    size_t offset = (size_t)offset_ll;
    size_t size = (size_t)range;

    if (size > SIZE_MAX / sizeof(long long)) {
        free(sorted);
        return 0;
    }

    long long *dp = (long long *)calloc(size, sizeof(long long));
    long long *new_dp = (long long *)calloc(size, sizeof(long long));
    if (dp == NULL || new_dp == NULL) {
        free(sorted);
        free(dp);
        free(new_dp);
        return 0;
    }

    dp[offset] = 1;

    for (int pos = 0; pos < n; pos++) {
        memset(new_dp, 0, size * sizeof(long long));
        for (size_t s = 0; s < size; s++) {
            if (dp[s] == 0) continue;
            long long cur_sum = (long long)s - (long long)offset;
            for (int v = 0; v < num_values; v++) {
                long long nsum;
                if (check_add_overflow_ll(cur_sum, sorted[v], &nsum) != 0) {
                    continue;
                }
                if (nsum >= 0 && nsum <= max_sum) {
                    long long idx_ll;
                    if (check_sub_overflow_ll(nsum, min_sum, &idx_ll) != 0) {
                        continue;
                    }
                    if (idx_ll < 0 || (size_t)idx_ll >= size) {
                        continue;
                    }
                    size_t idx = (size_t)idx_ll;
                    new_dp[idx] = (new_dp[idx] + dp[s]) % MOD;
                }
            }
        }
        long long *tmp = dp;
        dp = new_dp;
        new_dp = tmp;
    }

    long long result = 0;
    for (size_t s = offset; s < size; s++) {
        result = (result + dp[s]) % MOD;
    }

    free(sorted);
    free(dp);
    free(new_dp);
    return result;
}

int main(void) {
    const long long values1[] = {1, -1};
    printf("%lld\n", count_sequences(4, values1, 2));

    const long long values2[] = {1, 2, -1};
    printf("%lld\n", count_sequences(3, values2, 3));

    const long long values3[] = {1, -1, 0};
    printf("%lld\n", count_sequences(5, values3, 3));

    return 0;
}