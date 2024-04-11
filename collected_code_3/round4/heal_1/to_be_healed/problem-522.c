#include <stdio.h>
#include <stdlib.h>

int longestBitonic(int arr[], int n)
{
    int i, j;
    int *lis = (int *)malloc(sizeof(int) * n);
    int *lds = (int *)malloc(sizeof(int) * n);
    int max;

    for (i = 0; i < n; i++)
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'lds' [CWE-690] [-Wanalyzer-possible-null-dereference]
         *  dereference of possibly-NULL 'lis' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        lis[i] = lds[i] = 1;

    for (i = 1; i < n; i++)
        for (j = 0; j < i; j++)
            if (arr[i] > arr[j] && lis[i] < lis[j] + 1)
                lis[i] = lis[j] + 1;

    for (i = n - 2; i >= 0; i--)
        for (j = n - 1; j > i; j--)
            /* Possible weaknesses found:
             *  use of uninitialized value '*lds_102 + _45' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
             */
            if (arr[i] > arr[j] && lds[i] < lds[j] + 1)
                lds[i] = lds[j] + 1;

    max = lis[0] + lds[0] - 1;
    for (i = 1; i < n; i++)
        if (lis[i] + lds[i] - 1 > max)
            max = lis[i] + lds[i] - 1;

    free(lis);
    free(lds);

    return max;
}

int main()
{
    int arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Length of longest bitonic subsequence is %d\n", longestBitonic(arr, n));
    return 0;
}