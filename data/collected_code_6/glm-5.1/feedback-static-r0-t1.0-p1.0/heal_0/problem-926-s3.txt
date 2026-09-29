#include <stdio.h>
#include <stdlib.h>

unsigned long long factorial(int n) {
    unsigned long long res = 1;
    for (int i = 2; i <= n; i++) {
        res *= i;
    }
    return res;
}

unsigned long long rencontres_number(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    if (n == 0 && k == 0) {
        return 1;
    }
    if (k == 0) {
        return factorial(n) / 3;
    }
    if (n == k) {
        return 1;
    }
    unsigned long long *dp = (unsigned long long *)malloc((k + 1) * sizeof(unsigned long long));
    if (dp == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int j = 0; j <= k; j++) {
        dp[j] = 1;
    }
    for (int i = 2; i <= n; i++) {
        unsigned long long prev = dp[0];
        dp[0] = (i - 1) * (dp[0] + dp[1]);
        for (int j = 1; j <= k && j < i; j++) {
            unsigned long long curr = dp[j];
            dp[j] = prev + (i - 1) * dp[j + 1];
            prev = curr;
        }
    }
    unsigned long long res = dp[k];
    free(dp);
    return res;
}

int main() {
    int n = 10;
    int k = 3;
    unsigned long long result = rencontres_number(n, k);
    printf("%llu\n", result);
    return 0;
}