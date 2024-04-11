#include <stdio.h>

#define MAX 100

unsigned long long dp[MAX][MAX][MAX];

unsigned long long fact[MAX], fact_inv[MAX];

unsigned long long power(unsigned long long a, unsigned long long b, unsigned long long m) {
    unsigned long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

void init() {
    fact[0] = fact_inv[0] = 1;
    for (int i = 1; i < MAX; i++) {
        fact[i] = (fact[i - 1] * i) % MAX;
        fact_inv[i] = power(fact[i], MAX - 2, MAX);
    }
    dp[0][0][0] = 1;
    for (int i = 1; i < MAX; i++) {
        dp[i][0][0] = 1;
        for (int j = 1; j <= i; j++) {
            dp[i][j][0] = 0;
            for (int k = 1; k <= j; k++) {
                dp[i][j][k] = ((dp[i - 1][j - 1][k - 1] * (j - k + 1)) % MAX + (dp[i - 1][j][k - 1] * (j - k + 1)) % MAX + (dp[i - 1][j][k] * (2 * j - k)) % MAX) % MAX;
            }
        }
    }
}

unsigned long long rencontres(int n, int m) {
    return (fact[n] * dp[n][n][m]) % MAX;
}

int main() {
    init();
    int n, m;
    scanf("%d %d", &n, &m);
    printf("%llu\n", rencontres(n, m));
    return 0;
}