#include <stdio.h>
#include <limits.h>

int max(int a, int b) { return (a > b)? a : b; }

int maxSubArraySum(int a[], int size)
{
    int max_so_far = INT_MIN, max_ending_here = 0;
    for (int i = 0; i < size; i++)
    {
        max_ending_here = max_ending_here + a[i];
        if (max_so_far < max_ending_here)
            max_so_far = max_ending_here;
        if (max_ending_here < 0)
            max_ending_here = 0;
    }
    return max_so_far;
}

int maxSubArraySumKTimes(int a[], int n, int k)
{
    int max_single = maxSubArraySum(a, n);
    if (k == 1)
        return max_single;
    int max_prefix_sum = INT_MIN, max_suffix_sum = INT_MIN, total_sum = 0;
    int prefix_sum = 0, suffix_sum = 0;
    for (int i = 0; i < n; i++)
    {
        prefix_sum += a[i];
        max_prefix_sum = max(max_prefix_sum, prefix_sum);
        total_sum += a[i];
    }
    for (int i = n-1; i >= 0; i--)
    {
        suffix_sum += a[i];
        max_suffix_sum = max(max_suffix_sum, suffix_sum);
    }
    int ans;
    if (total_sum < 0)
        ans = max(max_single, max_prefix_sum + max_suffix_sum);
    else
        ans = max(max_single, max_prefix_sum + max_suffix_sum + (total_sum * (k-2)));
    return ans;
}

int main()
{
    int a[] = {1, 2, 3, 4};
    int n = sizeof(a)/sizeof(a[0]);
    int k = 3;
    printf("Maximum contiguous sum is %d\n", maxSubArraySumKTimes(a, n, k));
    return 0;
}