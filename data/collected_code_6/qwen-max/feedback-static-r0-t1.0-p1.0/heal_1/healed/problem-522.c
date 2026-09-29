#include <stdio.h>
#include <stdlib.h>

int *calculateLIS(const int arr[], int n, int *size) {
    int *lis = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        lis[i] = 1;
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (arr[i] > arr[j] && lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1;
            }
        }
    }
    *size = 0;
    for (int i = 0; i < n; ++i) {
        if (lis[*size] < lis[i]) {
            *size = i;
        }
    }
    return lis;
}

int *calculateLDS(const int arr[], int n, int *size) {
    int *lds = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        lds[i] = 1;
    }
    for (int i = n - 2; i >= 0; --i) {
        for (int j = n - 1; j > i; --j) {
            if (arr[i] > arr[j] && lds[i] < lds[j] + 1) {
                lds[i] = lds[j] + 1;
            }
        }
    }
    *size = 0;
    for (int i = 0; i < n; ++i) {
        if (lds[*size] < lds[i]) {
            *size = i;
        }
    }
    return lds;
}

int findLongestBitonicSubsequence(const int arr[], int n) {
    int lis_size = 0, lds_size = 0;
    int *lis = calculateLIS(arr, n, &lis_size);
    int *lds = calculateLDS(arr, n, &lds_size);

    int max_length = 0;
    for (int i = 0; i < n; ++i) {
        if (max_length < lis[i] + lds[i] - 1) {
            max_length = lis[i] + lds[i] - 1;
        }
    }

    free(lis);
    free(lds);

    return max_length;
}

int main() {
    const int arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findLongestBitonicSubsequence(arr, n);
    printf("Length of longest bitonic subsequence is %d\n", result);
    return 0;
}