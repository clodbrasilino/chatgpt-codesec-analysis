#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 1000000

static long long maxOfThree(long long a, long long b, long long c)
{
    long long m = (a > b) ? a : b;
    return (m > c) ? m : c;
}

int maxSumNoThreeConsecutive(const int *arr, size_t n, long long *result)
{
    long long *dp;
    size_t i;

    if (result == NULL)
    {
        return -1;
    }

    *result = 0LL;

    if (n == 0U)
    {
        return 0;
    }

    if (arr == NULL)
    {
        return -1;
    }

    if (n == 1U)
    {
        *result = (long long)arr[0];
        return 0;
    }

    if (n == 2U)
    {
        *result = (long long)arr[0] + (long long)arr[1];
        return 0;
    }

    dp = (long long *)malloc(n * sizeof(long long));
    if (dp == NULL)
    {
        return -1;
    }

    dp[0] = (long long)arr[0];
    dp[1] = maxOfThree((long long)arr[0] + (long long)arr[1],
                       (long long)arr[0],
                       (long long)arr[1]);
    dp[2] = maxOfThree((long long)arr[0] + (long long)arr[1],
                       (long long)arr[0] + (long long)arr[2],
                       (long long)arr[1] + (long long)arr[2]);

    for (i = 3U; i < n; i++)
    {
        dp[i] = maxOfThree(dp[i - 1U],
                           dp[i - 2U] + (long long)arr[i],
                           dp[i - 3U] + (long long)arr[i - 1U] + (long long)arr[i]);
    }

    *result = dp[n - 1U];

    free(dp);
    dp = NULL;

    return 0;
}

int main(void)
{
    int inputN;
    int *arr;
    size_t n;
    size_t i;
    long long result;

    printf("Enter number of elements: ");
    if (scanf("%d", &inputN) != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (inputN <= 0 || inputN > MAX_ELEMENTS)
    {
        fprintf(stderr, "Error: number of elements must be between 1 and %d.\n", MAX_ELEMENTS);
        return EXIT_FAILURE;
    }

    n = (size_t)inputN;

    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Enter %d element(s): ", inputN);
    for (i = 0U; i < n; i++)
    {
        if (scanf("%d", &arr[i]) != 1)
        {
            fprintf(stderr, "Error: invalid element value.\n");
            free(arr);
            arr = NULL;
            return EXIT_FAILURE;
        }
    }

    if (maxSumNoThreeConsecutive(arr, n, &result) != 0)
    {
        fprintf(stderr, "Error: failed to compute maximum sum.\n");
        free(arr);
        arr = NULL;
        return EXIT_FAILURE;
    }

    printf("Maximum sum with no three consecutive elements: %lld\n", result);

    free(arr);
    arr = NULL;

    return EXIT_SUCCESS;
}