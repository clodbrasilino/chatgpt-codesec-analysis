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

int maxSubArraySumK(int a[], int n, int k)
{
    int max_sum = maxSubArraySum(a, n);
    if (k == 1)
        return max_sum;
    int curr_prefix_sum = 0, curr_suffix_sum = 0;
    int max_prefix_sum = INT_MIN, max_suffix_sum = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        curr_prefix_sum += a[i];
        max_prefix_sum = max(max_prefix_sum, curr_prefix_sum);
    }
    int total_sum = curr_prefix_sum;
    for (int i = n - 1; i >= 0; i--)
    {
        curr_suffix_sum += a[i];
        max_suffix_sum = max(max_suffix_sum, curr_suffix_sum);
    }
    if (total_sum < 0)
        return max(max_sum, max_prefix_sum + max_suffix_sum);
    else
        return max(max_sum, max_prefix_sum + max_suffix_sum + total_sum * (k - 2));
}

int main()
{
    int a[] = {1, 2, 3, 4};
    int n = sizeof(a)/sizeof(a[0]);
    int k = 3;
    printf("Maximum contiguous sum is %d\n", maxSubArraySumK(a, n, k));
    return 0;
}