#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int max_disjoint_pair_sum(int *arr, int n, int k) {
    if (arr == NULL || n < 2 || k < 0) {
        return 0;
    }
    
    if ((size_t)n > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    
    int *sorted = malloc((size_t)n * sizeof(int));
    if (sorted == NULL) {
        return -1;
    }
    
    memcpy(sorted, arr, (size_t)n * sizeof(int));
    qsort(sorted, (size_t)n, sizeof(int), compare_ints);
    
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
            if ((sorted[left - 1] > 0 && sorted[right] > INT_MAX - sorted[left - 1]) ||
                (sorted[left - 1] < 0 && sorted[right] < INT_MIN - sorted[left - 1])) {
                free(sorted);
                free(dp);
                return -1;
            }
            int pair_sum = sorted[left - 1] + sorted[right];
            
            if ((dp[left] > 0 && pair_sum > INT_MAX - dp[left]) ||
                (dp[left] < 0 && pair_sum < INT_MIN - dp[left])) {
                free(sorted);
                free(dp);
                return -1;
            }
            int candidate = dp[left] + pair_sum;
            
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