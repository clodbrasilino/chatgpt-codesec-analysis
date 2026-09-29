#include <stdio.h>
#include <stdlib.h>
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

int maxSubArraySum_kTimes(int a[], int n, int k)
{
    int max_single_call = maxSubArraySum(a, n);
 
    if (k == 1)
        return max_single_call;
 
    int max_prefix_sum = INT_MIN, max_suffix_sum = INT_MIN;
    int curr_sum = 0;
    for (int i=0; i<n; i++)
    {
        curr_sum = curr_sum + a[i];
        max_prefix_sum = max(max_prefix_sum, curr_sum);
    }
 
    int sum_a = curr_sum;
    curr_sum = 0;
    for (int i=n-1; i>=0; i--)
    {
        curr_sum = curr_sum + a[i];
        max_suffix_sum = max(max_suffix_sum, curr_sum);
    }
 
    int max_two_calls = max(max_suffix_sum + sum_a*(k-2) + max_prefix_sum, max_prefix_sum + sum_a*(k-1));

    return max(max_single_call, max_two_calls);
}

int main() {
   int arr[] = {-1, -2, -3, -4, -5};
   int n = sizeof(arr)/sizeof(arr[0]);
   int k = 3;
   printf("Maximum subarray sum is %d\n", maxSubArraySum_kTimes(arr, n, k));
   return 0;
}