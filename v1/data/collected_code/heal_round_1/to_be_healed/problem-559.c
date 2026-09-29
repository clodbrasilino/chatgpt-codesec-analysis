#include <stdio.h>

int maxSubarraySum(int arr[], int n)
{
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int max_current = arr[0];
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int max_global = arr[0];
    
    for (int i = 1; i < n; i++)
    {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
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