#include <stdio.h>

int maxSubarraySum(int arr[], int n)
{
    int max_current = arr[0];
    int max_global = arr[0];
    
    for (int i = 1; i < n; i++)
    {
        max_current = (arr[i] > max_current + arr[i]) ? arr[i] : max_current + arr[i];
        if (max_current > max_global)
            max_global = max_current;
    }
    return max_global;
}

int main()
{
    int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Largest sum of contiguous subarray: %d\n", maxSubarraySum(arr, n));
    
    return 0;
}