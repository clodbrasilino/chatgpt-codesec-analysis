#include <stdio.h>
#include <limits.h>

int maxIncSubseqSum(int arr[], int n) {
    int i, j, maxSum = INT_MIN;
    int sum[n];
  
    for (i = 0; i < n; i++ )
        sum[i] = arr[i];
  
    for (i = 1; i < n; i++ )
        for (j = 0; j < i; j++ )
            if (arr[i] > arr[j] && sum[i] < sum[j] + arr[i])
                sum[i] = sum[j]+arr[i];
  
    for (i = 0; i < n; i++ )
        if (maxSum < sum[i])
            maxSum = sum[i];
  
    return maxSum;
}

int main() {
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Sum of maximum increasing subsequence is %d\n", maxIncSubseqSum( arr, n) );
    return 0;
}