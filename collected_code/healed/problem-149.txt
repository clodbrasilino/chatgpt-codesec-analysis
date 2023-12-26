#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestSubsequence(const int arr[], int n)
{
    int dp[n];
    int ans = 0;

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (arr[i] - arr[j] == 1 || arr[i] - arr[j] == -1) {
                dp[i] = dp[j] + 1;
                break;
            }
        }
        ans = max(ans, dp[i]);
    }

    return ans;
}

int main()
{
    const int arr[] = {1, 2, 3, 4, 5, 3, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    int length = longestSubsequence(arr, n);

    printf("Length of the longest subsequence with adjacent difference one: %d\n", length);

    return 0;
}