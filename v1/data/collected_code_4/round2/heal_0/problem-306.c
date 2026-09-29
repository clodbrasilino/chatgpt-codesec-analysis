#include <stdio.h>
#include <stdlib.h>

int maxSumIncSubseqWithK(int arr[], int n, int k)
{
    int i, j, max = 0, msis[n], maxSumK[n];
 
    for (i = 0; i < n; i++){
        msis[i] = arr[i];
        maxSumK[i] = 0;
    }
 
    for (i = 1; i < n; i++)
        for (j = 0; j < i; j++)
            if (arr[i] > arr[j] && msis[i] < msis[j] + arr[i])
                msis[i] = msis[j] + arr[i];
 
    for (i = 0 ; i < n ; i++ )
        if ( max < msis[i])
            max = msis[i];
     
    for (i = 0; i < n; i++)
        if (msis[i] == max)
            maxSumK[i] = arr[i];
        else
            maxSumK[i] = 0;
 
    for(i = k; i < n; i++)
        if(maxSumK[i] > 0)
            max += arr[i];
 
    return max;
}

int main(){
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 4;
    printf("Maximum sum of increasing subsequence including kth element is %d\n",
           maxSumIncSubseqWithK(arr, n, k));
    return 0;
}