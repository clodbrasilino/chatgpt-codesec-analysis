#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long maxSubArraySum(const int *arr, int n) {
    long long max_so_far = LLONG_MIN;
    long long max_ending_here = 0;
    
    for (int i = 0; i < n; i++) {
        max_ending_here += arr[i];
        
        if (max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
        }
        
        if (max_ending_here < 0) {
            max_ending_here = 0;
        }
    }
    
    return max_so_far;
}

long long maxSubArraySumRepeated(const int *arr, int n, int k) {
    if (arr == NULL || n <= 0 || k <= 0) {
        return 0;
    }
    
    long long max_sum_single = maxSubArraySum(arr, n);
    
    if (k == 1) {
        return max_sum_single;
    }
    
    long long total_sum = 0;
    for (int i = 0; i < n; i++) {
        total_sum += arr[i];
    }
    
    long long max_prefix = LLONG_MIN;
    long long current_prefix = 0;
    for (int i = 0; i < n; i++) {
        current_prefix += arr[i];
        if (current_prefix > max_prefix) {
            max_prefix = current_prefix;
        }
    }
    
    long long max_suffix = LLONG_MIN;
    long long current_suffix = 0;
    for (int i = n - 1; i >= 0; i--) {
        current_suffix += arr[i];
        if (current_suffix > max_suffix) {
            max_suffix = current_suffix;
        }
    }
    
    long long result = max_sum_single;
    
    if (total_sum > 0) {
        long long candidate = max_prefix + max_suffix + (k - 2) * total_sum;
        if (candidate > result) {
            result = candidate;
        }
    } else {
        long long candidate = max_prefix + max_suffix;
        if (candidate > result) {
            result = candidate;
        }
    }
    
    return result;
}

int main(void) {
    int n, k;
    
    if (scanf("%d %d", &n, &k) != 2) {
        return EXIT_FAILURE;
    }
    
    if (n <= 0 || k <= 0) {
        return EXIT_FAILURE;
    }
    
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return EXIT_FAILURE;
        }
    }
    
    long long result = maxSubArraySumRepeated(arr, n, k);
    printf("%lld\n", result);
    
    free(arr);
    arr = NULL;
    
    return EXIT_SUCCESS;
}