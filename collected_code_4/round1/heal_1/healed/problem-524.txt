#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxSumOfIncSubseq(int arr[], int n) {
    int *maxsum;
    int i, j, maxSum = 0;

    maxsum = (int*)malloc(sizeof(int) * n);
    if(maxsum == NULL)
        return maxSum;

    for (i = 0; i < n; i++)
        maxsum[i] = arr[i];

    for (i = 1; i < n; i++ )
        for (j = 0; j < i; j++ )
            if (arr[i] > arr[j] && maxsum[i] < maxsum[j] + arr[i])
                maxsum[i] = maxsum[j] + arr[i];

    for (i = 0; i < n; i++ )
        if (maxSum < maxsum[i])
            maxSum = maxsum[i];

    free(maxsum);

    return maxSum;
}

int main() {
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Sum of maximum increasing subsequence is %d", 
            maxSumOfIncSubseq( arr, n ) );

    return 0;
}