#include <stdio.h>
#include <stdlib.h>

int maxSumISwithK(int arr[], int n, int k) 
{ 
    int i, j, msisk, max = 0;
    int* msis = (int*)malloc(sizeof(int) * n); 

    for (i = 0; i < n; i++)  
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'msis' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        msis[i] = arr[i]; 

    for (i = 1; i < k; i++) 
        for (j = 0; j < i; j++) 
            /* Possible weaknesses found:
             *  use of uninitialized value '*msis_112 + _19' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
             */
            if (arr[i] > arr[j] && msis[i] < msis[j] + arr[i]) 
                msis[i] = msis[j] + arr[i]; 
  
    /* Possible weaknesses found:
     *  use of uninitialized value '*msis_112 + _45' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    msisk = msis[k-1]; 
    for (i = k; i < n; i++) 
        for (j = 0; j < i; j++) 
            if (arr[i] > arr[j] && msis[i] < msis[j] + arr[i]) 
                msis[i] = msis[j] + arr[i]; 
          
    free(msis);
    for (i = k; i < n; i++) 
        /* Possible weaknesses found:
         *  use of uninitialized value '*msis_112 + _81' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        if (max < msis[i]) 
            max = msis[i]; 

    return max - arr[k - 1] + msisk;
}

int main()
{
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    int k = 4;
    printf("Maximum sum is %d\n", maxSumISwithK(arr, n, k));
  
    return 0;
}