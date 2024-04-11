#include <stdio.h>

long long dp[1000][1000];

long long C(int n, int r) {
    if(r == 0 || n == r) return 1;
    if(r == 1) return n;
    if(dp[n][r]) return dp[n][r];
    return dp[n][r] = C(n - 1, r - 1) + C(n - 1, r);
}

long long rencontres(int n, int m) {
    if(n == 0 && m == 0) return 1;
    if(n == 0 || m == 0) return 0;
    return (rencontres(n - 1, m) + rencontres(n - 1, m - 1) * (n - 1)) % 1000000007;
}

int main() {
    int n;
    printf("Enter the number: ");
    scanf("%d", &n);
    printf("The %d-th rencontres number is: %lld\n", n, rencontres(n, n));
    return 0;
}