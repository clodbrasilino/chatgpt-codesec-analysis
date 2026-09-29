#include <stdio.h>
#include <stdlib.h>

int longestBitonicSubsequence(const int *arr, int n)
{
    int *lis;
    int *lds;
    int i;
    int j;
    int maxLen;

    if (arr == NULL || n <= 0) {
        return 0;
    }

    lis = (int *)malloc((size_t)n * sizeof(int));
    if (lis == NULL) {
        return -1;
    }

    lds = (int *)malloc((size_t)n * sizeof(int));
    if (lds == NULL) {
        free(lis);
        return -1;
    }

    for (i = 0; i < n; i++) {
        lis[i] = 1;
        lds[i] = 1;
    }

    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (arr[i] > arr[j] && lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1;
            }
        }
    }

    for (i = n - 2; i >= 0; i--) {
        for (j = n - 1; j > i; j--) {
            if (arr[i] > arr[j] && lds[i] < lds[j] + 1) {
                lds[i] = lds[j] + 1;
            }
        }
    }

    maxLen = lis[0] + lds[0] - 1;
    for (i = 1; i < n; i++) {
        if (lis[i] + lds[i] - 1 > maxLen) {
            maxLen = lis[i] + lds[i] - 1;
        }
    }

    free(lis);
    free(lds);

    return maxLen;
}

int main(void)
{
    int arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));
    int result;

    result = longestBitonicSubsequence(arr, n);
    if (result < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("Length of longest bitonic subsequence: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}