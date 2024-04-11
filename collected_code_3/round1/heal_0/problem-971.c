#include <stdio.h>

int maxSegments(int n, int a, int b, int c) {
    int dp[n+1];
    dp[0] = 0;
    for(int i=1; i<=n; i++) {
        dp[i] = -1;
        if(i-a >= 0) dp[i] = dp[i] > dp[i-a]+1 ? dp[i] : dp[i-a]+1;
        if(i-b >= 0) dp[i] = dp[i] > dp[i-b]+1 ? dp[i] : dp[i-b]+1;
        if(i-c >= 0) dp[i] = dp[i] > dp[i-c]+1 ? dp[i] : dp[i-c]+1;
    }
    return dp[n];
}

int main() {
    int n = 7;
    int a = 5;
    int b = 2;
    int c = 1;
    printf("%d", maxSegments(n, a, b, c));
    return 0;
}