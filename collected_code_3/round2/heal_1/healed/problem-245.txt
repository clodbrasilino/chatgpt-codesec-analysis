#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int maxSumBitonic(int *arr, int n) {
    int *msis = (int *) malloc(sizeof(int) * n);
    int *msds = (int *) malloc(sizeof(int) * n);
    int max_sum = 0, i, j;

    if (!msis || !msds) {
        return -1;
    }
    
    for (i = 0; i < n; i++) {
        msis[i] = arr[i];
        msds[i] = arr[i];
    }

    for (i = 1; i < n; i++)
        for (j = 0; j < i; j++)
            if (arr[i] > arr[j] && msis[i] < msis[j] + arr[i])
                msis[i] = msis[j] + arr[i];

    for (i = n - 2; i >= 0; i--)
        for (j = n - 1; j > i; j--)
            if (arr[i] > arr[j] && msds[i] < msds[j] + arr[i])
                msds[i] = msds[j] + arr[i];

    for (i = 0; i < n; i++)
        max_sum = max(max_sum, msis[i] + msds[i] - arr[i]);

    free(msis);
    free(msds);

    return max_sum;
}

int main() {
    int arr[] = {1, 15, 51, 45, 33, 100, 12, 18, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Maximum Sum Bi-tonic sub-sequence is %d\n", maxSumBitonic(arr, n));
    return 0;
}