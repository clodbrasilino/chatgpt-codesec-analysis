#include <stdio.h>

long long countWays(int n, int k) {
    long long dp[2];
    dp[0] = k;
    dp[1] = k * k;

    if(n <= 2) {
        return dp[n-1];
    }

    int same = 0, diff = 0;
    for(int i = 2; i < n; i++) {
        same = diff;
        diff = dp[1] * (k-1);
        dp[1] = same + diff;
    }

    return dp[1];
}

int main() {
    int n, k;
    printf("Enter the number of posts: ");
    scanf("%d", &n);
    printf("Enter the number of colors: ");
    scanf("%d", &k);

    printf("Number of ways to paint the fence: %lld\n", countWays(n, k));

    return 0;
}