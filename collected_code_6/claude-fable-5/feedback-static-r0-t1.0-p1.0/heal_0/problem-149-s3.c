#include <stdio.h>
#include <stdlib.h>

int longestSubsequence(const int *arr, int n)
{
    int *dp;
    int i;
    int j;
    int result;

    if (arr == NULL || n <= 0)
    {
        return 0;
    }

    dp = (int *)malloc((size_t)n * sizeof(int));
    if (dp == NULL)
    {
        return -1;
    }

    for (i = 0; i < n; i++)
    {
        dp[i] = 1;
    }

    result = 1;

    for (i = 1; i < n; i++)
    {
        for (j = 0; j < i; j++)
        {
            if ((arr[i] == arr[j] + 1) || (arr[i] == arr[j] - 1))
            {
                if (dp[j] + 1 > dp[i])
                {
                    dp[i] = dp[j] + 1;
                }
            }
        }
        if (dp[i] > result)
        {
            result = dp[i];
        }
    }

    free(dp);
    dp = NULL;

    return result;
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5, 3, 2};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));
    int result;

    result = longestSubsequence(arr, n);
    if (result < 0)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("Length of the longest subsequence: %d\n", result) < 0)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}