#include <stdio.h>
#include <stdlib.h>

int maxBitonicSum(const int arr[], int n)
{
    int *msis;
    int *msds;
    int i;
    int j;
    int max_sum;

    if (arr == NULL || n <= 0) {
        return 0;
    }

    msis = malloc((size_t)n * sizeof(int));
    if (msis == NULL) {
        return 0;
    }

    msds = malloc((size_t)n * sizeof(int));
    if (msds == NULL) {
        free(msis);
        return 0;
    }

    for (i = 0; i < n; i++) {
        msis[i] = arr[i];
        for (j = 0; j < i; j++) {
            if (arr[j] < arr[i] && msis[j] + arr[i] > msis[i]) {
                msis[i] = msis[j] + arr[i];
            }
        }
    }

    for (i = n - 1; i >= 0; i--) {
        msds[i] = arr[i];
        for (j = n - 1; j > i; j--) {
            if (arr[j] < arr[i] && msds[j] + arr[i] > msds[i]) {
                msds[i] = msds[j] + arr[i];
            }
        }
    }

    max_sum = msis[0] + msds[0] - arr[0];
    for (i = 1; i < n; i++) {
        if (msis[i] + msds[i] - arr[i] > max_sum) {
            max_sum = msis[i] + msds[i] - arr[i];
        }
    }

    free(msis);
    free(msds);

    return max_sum;
}

int main(void)
{
    int arr[] = {1, 15, 51, 45, 33, 100, 12, 18, 9};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));
    int result;

    result = maxBitonicSum(arr, n);
    printf("Maximum sum of bi-tonic subsequence: %d\n", result);

    return 0;
}