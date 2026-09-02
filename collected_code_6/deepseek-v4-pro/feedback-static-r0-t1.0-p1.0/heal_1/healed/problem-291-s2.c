#include <stdlib.h>
#include <stdio.h>

long long countWays(int n, int k) {
    if (n <= 0 || k <= 0) {
        return 0;
    }

    if (n == 1) {
        return k;
    }

    if (k == 1) {
        if (n == 2) {
            return 1;
        }
        return 0;
    }

    long long *same = (long long*)malloc((n + 1) * sizeof(long long));
    long long *diff = (long long*)malloc((n + 1) * sizeof(long long));
    if (same == NULL || diff == NULL) {
        free(same);
        free(diff);
        return -1;
    }

    same[1] = 0;
    diff[1] = k;

    for (int i = 2; i <= n; i++) {
        same[i] = diff[i - 1];
        diff[i] = (same[i - 1] + diff[i - 1]) * (k - 1);
    }

    long long result = same[n] + diff[n];
    free(same);
    free(diff);
    return result;
}

int main(void) {
    int n = 3;
    int k = 2;
    long long result = countWays(n, k);
    if (result >= 0) {
        printf("%lld\n", result);
    } else {
        printf("Error\n");
    }
    return 0;
}