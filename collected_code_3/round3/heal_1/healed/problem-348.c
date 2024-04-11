#include <stdio.h>
#include <string.h>

#define MAX 100

int dp[MAX][MAX];

int countSeq(int arr[], int n, int len, int sum) {
    if (len == 0)
        return sum >= 0;
    if (dp[len][sum + MAX] != -1)
        return dp[len][sum + MAX];
    int res = 0;
    for (int i = 0; i < n; i++)
        if (sum - arr[i] >= -MAX)
            res += countSeq(arr, n, len - 1, sum - arr[i]);
    return (dp[len][sum + MAX] = res);
}

int countSeqUtil(int arr[], int n, int len) {
    memset(dp, -1, sizeof dp);
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    int ans = 0;
    for (int i = 0; i < n; i++)
        ans += countSeq(arr, n, len - 1, sum - arr[i]);
    return ans;
}

int main() {
    int arr[] = {1, 2, 3};
    int len = 3;
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d", countSeqUtil(arr, n, len));
    return 0;
}