#include <stdio.h>

int isSubsetDivisible(int arr[], int n, int m)
{
    if (n > m)
        return 1;

    int dp[m];
    for (int i = 0; i < m; i++)
        dp[i] = 0;

    for (int i = 0; i < n; i++)
    {
        int mod = arr[i] % m;
        dp[mod]++;
    }

    if (dp[0])
        return 1;

    for (int i = 1; i <= m / 2; i++)
        if (dp[i] != dp[m - i])
            return 0;

    if (m % 2 == 0 && dp[m / 2] % 2 != 0)
        return 0;

    return 1;
}

int main()
{
    int arr[] = {3, 1, 7, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int m = 6;

    if (isSubsetDivisible(arr, n, m))
        printf("There is a subset with sum divisible by m\n");
    else
        printf("There is no subset with sum divisible by m\n");

    return 0;
}