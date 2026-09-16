#include <stdio.h>
#include <stdlib.h>

int longestBitonicSubsequence(int arr[], int n);

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    int *arr = malloc((size_t)n * sizeof(*arr));
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }

    int result = longestBitonicSubsequence(arr, n);
    if (result == -1) {
        free(arr);
        return 1;
    }

    printf("%d\n", result);
    free(arr);
    return 0;
}

int longestBitonicSubsequence(int arr[], int n)
{
    if (n <= 0) {
        return 0;
    }

    int *inc = malloc((size_t)n * sizeof(*inc));
    int *dec = malloc((size_t)n * sizeof(*dec));

    if (inc == NULL || dec == NULL) {
        free(inc);
        free(dec);
        return -1;
    }

    for (int i = 0; i < n; i++) {
        inc[i] = 1;
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && inc[i] < inc[j] + 1) {
                inc[i] = inc[j] + 1;
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        dec[i] = 1;
        for (int j = n - 1; j > i; j--) {
            if (arr[i] > arr[j] && dec[i] < dec[j] + 1) {
                dec[i] = dec[j] + 1;
            }
        }
    }

    int max = 0;
    for (int i = 0; i < n; i++) {
        int len = inc[i] + dec[i] - 1;
        if (len > max) {
            max = len;
        }
    }

    free(inc);
    free(dec);
    return max;
}