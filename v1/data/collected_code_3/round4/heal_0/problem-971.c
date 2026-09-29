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
    int n, a, b, c;
    printf("Enter the total length: ");
    scanf("%d", &n);
    printf("Enter the lengths of the segments: ");
    scanf("%d %d %d", &a, &b, &c);
    printf("The maximum number of segments that can be formed is %d\n", maxSegments(n, a, b, c));
    return 0;
}