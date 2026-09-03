#include <stdio.h>
#include <stdlib.h>

int longest_bitonic_subsequence(const int arr[], int n) {
    if (n <= 0) return 0;
    
    int *inc = (int*)malloc(n * sizeof(int));
    int *dec = (int*)malloc(n * sizeof(int));
    
    if (inc == NULL || dec == NULL) {
        free(inc);
        free(dec);
        return -1;
    }
    
    for (int i = 0; i < n; i++) {
        inc[i] = 1;
        dec[i] = 1;
    }
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && inc[i] < inc[j] + 1) {
                inc[i] = inc[j] + 1;
            }
        }
    }
    
    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (arr[i] > arr[j] && dec[i] < dec[j] + 1) {
                dec[i] = dec[j] + 1;
            }
        }
    }
    
    int max_len = 0;
    for (int i = 0; i < n; i++) {
        int current = inc[i] + dec[i] - 1;
        if (current > max_len) {
            max_len = current;
        }
    }
    
    free(inc);
    free(dec);
    return max_len;
}

int main() {
    int arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int result = longest_bitonic_subsequence(arr, n);
    if (result != -1) {
        printf("Length of longest bitonic subsequence: %d\n", result);
    } else {
        printf("Memory allocation failed\n");
    }
    
    int arr2[] = {12, 11, 40, 5, 3, 1};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    result = longest_bitonic_subsequence(arr2, n2);
    if (result != -1) {
        printf("Length of longest bitonic subsequence: %d\n", result);
    } else {
        printf("Memory allocation failed\n");
    }
    
    int arr3[] = {80, 60, 30, 40, 20, 10};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    
    result = longest_bitonic_subsequence(arr3, n3);
    if (result != -1) {
        printf("Length of longest bitonic subsequence: %d\n", result);
    } else {
        printf("Memory allocation failed\n");
    }
    
    return 0;
}