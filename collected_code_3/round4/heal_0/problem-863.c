#include <stdio.h>
#include <stdlib.h>

int findLongestConseqSubseq(int arr[], int n)
{
    int hash[100000] = {0};
    int i;
    for (i = 0; i < n; i++)
        hash[arr[i]] = 1;
    int res = 0;
    for (i = 0; i < n; i++)
    {
        if (!hash[arr[i] - 1])
        {
            int j = arr[i];
            while (hash[j])
                j++;
            if (res < j - arr[i])
                res = j - arr[i];
        }
    }
    return res;
}

int main()
{
    int arr[] = {1, 9, 3, 10, 4, 20, 2};
    int n = sizeof arr / sizeof arr[0];
    printf("Length of the Longest contiguous subsequence is %d\n",
           findLongestConseqSubseq(arr, n));
    return 0;
}