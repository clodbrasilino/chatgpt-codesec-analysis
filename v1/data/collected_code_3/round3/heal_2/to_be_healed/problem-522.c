#include <stdio.h>
#include <stdlib.h>

int longestBitonic(int arr[], int n)
{
    int i, j;
    int *lis = (int *)malloc(sizeof(int) * n);
    int *lds = (int *)malloc(sizeof(int) * n);
    int max;

    if (lis == NULL || lds == NULL)
        /* Possible weaknesses found:
         *  leak of 'lis' [CWE-401] [-Wanalyzer-malloc-leak]
         *  leak of 'lds' [CWE-401] [-Wanalyzer-malloc-leak]
         */
        return -1;
    
    for (i = 0; i < n; i++)
        lis[i] = lds[i] = 1;

    for (i = 1; i < n; i++)
        for (j = 0; j < i; j++)
            if (arr[i] > arr[j] && lis[i] < lis[j] + 1)
                lis[i] = lis[j] + 1;

    for (i = n - 2; i >= 0; i--)
        for (j = n - 1; j > i; j--)
            if (arr[i] > arr[j] && lds[i] < (lds[j] + 1))
                lds[i] = lds[j] + 1;

    max = lis[0] + lds[0] - 1;
    for (i = 1; i < n; i++)
        if (lis[i] + lds[i] - 1 > max)
            max = lis[i] + lds[i] - 1;

    free(lis);
    lis = NULL;
    free(lds);
    lds = NULL;    

    return max;
}

int main()
{
    int arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Length of longest bitonic subsequence is %d\n", longestBitonic(arr, n));
    return 0;
}