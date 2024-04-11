#include <stdio.h>

#define MAX 100

long long dp[MAX][MAX];

long long fact[MAX], invFact[MAX];

long long power(long long a, long long b, long long m) {
    long long res = 1;
    while (b) {
        if (b & 1) {
            res = (res * a) % m;
        }
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

void precompute() {
    fact[0] = invFact[0] = 1;
    for (int i = 1; i < MAX; i++) {
        fact[i] = (i * fact[i - 1]) % 1000000007;
        invFact[i] = power(fact[i], 1000000007 - 2, 1000000007);
    }
}

long long C(int n, int k) {
    if (k > n) {
        return 0;
    }
    return fact[n] * invFact[k] % 1000000007 * invFact[n - k] % 1000000007;
}

long long rencontres(int n, int m) {
    if (n == 0 && m == 0) {
        return 1;
    }
    if (n == 0 || m == 0) {
        return 0;
    }
    if (dp[n][m] != -1) {
        return dp[n][m];
    }
    dp[n][m] = (rencontres(n - 1, m) + (n - 1) * rencontres(n - 1, m - 1)) % 1000000007;
    return dp[n][m];
}

int main() {
    int n;
    scanf("%d", &n);
    precompute();
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = -1;
        }
    }
    long long ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = (ans + C(n, i) * rencontres(i, i)) % 1000000007;
    }
    printf("%lld\n", ans);
    return 0;
}