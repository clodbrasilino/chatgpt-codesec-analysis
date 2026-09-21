#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int max_disjoint_pair_sum(int *arr, int n, int k) {
    if (arr == NULL || n < 2) {
        return 0;
    }
    
    if ((size_t)n > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    
    size_t elem_size = sizeof(int);
    size_t total_size = (size_t)n * elem_size;
    
    if (total_size / elem_size != (size_t)n) {
        return -1;
    }
    
    int *sorted = malloc(total_size);
    if (sorted == NULL) {
        return -1;
    }
    
    if (total_size > 0) {
        memcpy(sorted, arr, total_size);
    }
    qsort(sorted, (size_t)n, sizeof(int), compare_ints);
    
    if ((size_t)n + 1 > SIZE_MAX / sizeof(int)) {
        free(sorted);
        return -1;
    }
    
    int *dp = calloc((size_t)n + 1, sizeof(int));
    if (dp == NULL) {
        free(sorted);
        return -1;
    }
    
    int left = 0;
    for (int right = 0; right < n; right++) {
        while (left < right && sorted[right] - sorted[left] >= k) {
            left++;
        }
        
        dp[right + 1] = dp[right];
        
        if (left > 0) {
            int candidate = dp[left] + sorted[left - 1] + sorted[right];
            if (candidate > dp[right + 1]) {
                dp[right + 1] = candidate;
            }
        }
    }
    
    int result = dp[n];
    free(sorted);
    free(dp);
    return result;
}

int main(void) {
    int arr[] = {1, 4, 3, 8, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
    
    int result = max_disjoint_pair_sum(arr, n, k);
    printf("Maximum sum: %d\n", result);
    
    return 0;
}