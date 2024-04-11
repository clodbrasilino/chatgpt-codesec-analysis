#include <stdio.h>

long long dp[1000][1000];

long long fact(int n) {
    long long res = 1;
    for (int i = 2; i <= n; i++)
        res *= i;
    return res;
}

long long countRencontres(int n, int m) {
    if (n == 0 && m == 0)
        return 1;
    if (n == 0 || m == 0)
        return 0;
    if (dp[n][m] != -1)
        return dp[n][m];
    dp[n][m] = (n - 1) * (countRencontres(n - 1, m) + countRencontres(n - 2, m - 1));
    return dp[n][m];
}

int nthRencontres(int n) {
    for (int i = 0; i < 1000; i++)
        for (int j = 0; j < 1000; j++)
            dp[i][j] = -1;
    return fact(n) * countRencontres(n, 0) / fact(n);
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("The %d-th rencontres number is: %d\n", n, nthRencontres(n));
    return 0;
}