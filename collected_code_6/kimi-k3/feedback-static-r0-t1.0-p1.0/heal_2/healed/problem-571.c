#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

bool safe_add_int(int a, int b, int *result) {
    if (a > 0 && b > INT_MAX - a) {
        return false;
    }
    if (a < 0 && b < INT_MIN - a) {
        return false;
    }
    *result = a + b;
    return true;
}

bool safe_multiply_size(size_t a, size_t b, size_t *result) {
    if (a != 0 && b > SIZE_MAX / a) {
        return false;
    }
    *result = a * b;
    return true;
}

int max_disjoint_pair_sum(const int *arr, int n, int k) {
    if (arr == NULL || n < 2 || k < 0) {
        return 0;
    }
    
    size_t alloc_size;
    if (!safe_multiply_size((size_t)n, sizeof(int), &alloc_size)) {
        return -1;
    }
    
    int *sorted = malloc(alloc_size);
    if (sorted == NULL) {
        return -1;
    }
    
    for (int i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }
    
    qsort(sorted, (size_t)n, sizeof(int), compare_ints);
    
    size_t dp_size;
    if (!safe_multiply_size((size_t)n + 1, sizeof(int), &dp_size)) {
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
            int pair_sum;
            if (!safe_add_int(sorted[left - 1], sorted[right], &pair_sum)) {
                free(sorted);
                free(dp);
                return -1;
            }
            
            int candidate;
            if (!safe_add_int(dp[left], pair_sum, &candidate)) {
                free(sorted);
                free(dp);
                return -1;
            }
            
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