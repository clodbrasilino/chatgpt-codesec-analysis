#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int lis(const int arr[], int n) {
    int *lis = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i)
        lis[i] = 1;
    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            if (arr[i] > arr[j] && lis[i] < lis[j] + 1)
                lis[i] = lis[j] + 1;
    int max_val = lis[0];
    for (int i = 1; i < n; i++)
        if (max_val < lis[i])
            max_val = lis[i];
    free(lis);
    return max_val;
}

int lds(const int arr[], int n) {
    int *lds = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i)
        lds[i] = 1;
    for (int i = n - 2; i >= 0; --i)
        for (int j = n - 1; j > i; --j)
            if (arr[i] > arr[j] && lds[i] < lds[j] + 1)
                lds[i] = lds[j] + 1;
    int max_val = lds[n - 1];
    for (int i = n - 2; i >= 0; --i)
        if (max_val < lds[i])
            max_val = lds[i];
    free(lds);
    return max_val;
}

int longestBitonicSubsequence(const int arr[], int n) {
    int max_length = 0;
    for (int i = 0; i < n; ++i) {
        int lis_length = lis(arr, i + 1);
        int lds_length = lds(arr + i, n - i);
        int length = lis_length + lds_length - 1;
        if (length > max_length) {
            max_length = length;
        }
    }
    return max_length;
}

int main() {
    int arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Length of the longest bitonic subsequence is %d\n", longestBitonicSubsequence(arr, n));
    return 0;
}