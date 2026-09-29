#include <stdio.h>
#include <limits.h>

int maxProductSubsequence(int arr[], int n) {
    int *max_end = (int *)malloc(n * sizeof(int));
    if (max_end == NULL) return 0;
    
    for (int i = 0; i < n; ++i) {
        max_end[i] = arr[i];
    }
    
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (arr[i] > arr[j] && max_end[i] < max_end[j] * arr[i]) {
                max_end[i] = max_end[j] * arr[i];
            }
        }
    }
    
    int max_product = INT_MIN;
    for (int i = 0; i < n; ++i) {
        if (max_product < max_end[i]) {
            max_product = max_end[i];
        }
    }
    
    free(max_end);
    return max_product;
}

int main() {
    int arr[] = {3, 100, 4, 5, 150, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = maxProductSubsequence(arr, n);
    printf("Maximum product of an increasing subsequence is %d\n", result);
    return 0;
}