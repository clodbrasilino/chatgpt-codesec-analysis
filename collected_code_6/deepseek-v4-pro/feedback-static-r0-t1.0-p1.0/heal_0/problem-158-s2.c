#include <stdio.h>
#include <stdlib.h>

int minOperations(int arr[], int n, int k) {
    if (n <= 0 || k <= 0 || k > n) {
        return -1;
    }
    
    int *freq = calloc(101, sizeof(int));
    if (freq == NULL) {
        return -1;
    }
    
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0 || arr[i] > 100) {
            free(freq);
            return -1;
        }
        freq[arr[i]]++;
    }
    
    int idx = n - k;
    int sum = 0;
    
    for (int i = 100; i >= 0; i--) {
        if (freq[i] > 0) {
            for (int j = 0; j < freq[i]; j++) {
                if (sum >= idx) {
                    free(freq);
                    return count_operations(arr, n, k);
                }
                sum++;
            }
        }
    }
    
    free(freq);
    return count_operations(arr, n, k);
}

int count_operations(int arr[], int n, int k) {
    if (n <= 0 || k <= 0 || k > n) {
        return -1;
    }
    
    int max_val = arr[0];
    int min_val = arr[0];
    
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) max_val = arr[i];
        if (arr[i] < min_val) min_val = arr[i];
    }
    
    if (max_val == min_val) {
        return 0;
    }
    
    int *freq = calloc(max_val - min_val + 1, sizeof(int));
    if (freq == NULL) {
        return -1;
    }
    
    for (int i = 0; i < n; i++) {
        freq[arr[i] - min_val]++;
    }
    
    int target = 0;
    int max_freq = 0;
    
    for (int i = 0; i <= max_val - min_val; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            target = i + min_val;
        }
    }
    
    int operations = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] != target) {
            operations++;
        }
    }
    
    free(freq);
    
    if (operations <= k) {
        return operations;
    }
    
    return operations - k;
}

int main(void) {
    int n, k;
    
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }
    
    if (scanf("%d", &k) != 1 || k <= 0 || k > n) {
        return 1;
    }
    
    int *arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }
    
    int result = minOperations(arr, n, k);
    printf("%d\n", result);
    
    free(arr);
    return 0;
}