#include <stdio.h>
#include <stdlib.h>

long long countWays(int n, int k) {
    if (n == 0 || k == 0) {
        return 0;
    }
    if (n == 1) {
        return k;
    }

    long long same = k;
    long long diff;
    if (__builtin_mul_overflow((long long)k, k - 1, &diff)) {
        return -1;
    }
    long long total;
    if (__builtin_add_overflow(same, diff, &total)) {
        return -1;
    }

    for (int i = 3; i <= n; i++) {
        same = diff;
        if (__builtin_mul_overflow(total, k - 1, &diff)) {
            return -1;
        }
        if (__builtin_add_overflow(same, diff, &total)) {
            return -1;
        }
    }

    return total;
}

int main(void) {
    int n;
    int k;

    if (scanf("%d %d", &n, &k) != 2) {
        return 1;
    }

    if (n < 0 || k < 0) {
        return 1;
    }

    long long ways = countWays(n, k);
    printf("%lld\n", ways);

    return 0;
}