#include <stdio.h>
#include <stdlib.h>

int maxSumWithoutThreeConsec(int arr[], int n) {
    if(n == 0)
        return 0;
    else if(n == 1)
        return arr[0];
    else if(n == 2)
        return arr[0] + arr[1];

    int dp[n];

    dp[0] = arr[0];
    dp[1] = arr[0] + arr[1];
    dp[2] = ((arr[0] + arr[2]) > arr[1]) ? (arr[0] + arr[2]) : arr[1];

    for (int i = 3; i < n; i++){
        dp[i] = ((dp[i-1]) > (dp[i-2] + arr[i])) ? (dp[i-1]) : (dp[i-2] + arr[i]);
        dp[i] = ((dp[i]) > (dp[i-3] + arr[i-1] + arr[i])) ? (dp[i]) : (dp[i-3] + arr[i-1] + arr[i]);
    }

    return dp[n-1];
}

int main() {
    int arr[] = {100, 1000, 100, 1000, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", maxSumWithoutThreeConsec(arr, n));
    return 0;
}