#include <stdio.h>
#include <stdlib.h>

unsigned long long findBinarySequencesCount(int n) {
    if (n <= 0) {
        return 0;
    }

    int size = n + 1;
    unsigned long long *dp = (unsigned long long *)malloc(size * sizeof(unsigned long long));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i < size; i++) {
        dp[i] = 0;
    }
    dp[0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = i; j >= 1; j--) {
            dp[j] += dp[j - 1];
        }
    }

    unsigned long long count = 0;
    for (int i = 0; i < size; i++) {
        count += dp[i] * dp[i];
    }

    free(dp);
    return count;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n < 0) {
        return 1;
    }

    unsigned long long result = findBinarySequencesCount(n);
    printf("%llu\n", result);

    return 0;
}