#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long max_subarray_sum(const int arr[], int n) {
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

long long max_sum_repeated_array(const int arr[], int n, int k) {
    if (n <= 0 || k <= 0) {
        return 0;
    }

    long long single_max = max_subarray_sum(arr, n);
    
    if (k == 1) {
        return single_max;
    }

    long long total_sum = 0;
    for (int i = 0; i < n; i++) {
        total_sum += arr[i];
    }

    long long prefix_sum = 0;
    long long max_prefix = LLONG_MIN;
    for (int i = 0; i < n; i++) {
        prefix_sum += arr[i];
        if (prefix_sum > max_prefix) {
            max_prefix = prefix_sum;
        }
    }

    long long suffix_sum = 0;
    long long max_suffix = LLONG_MIN;
    for (int i = n - 1; i >= 0; i--) {
        suffix_sum += arr[i];
        if (suffix_sum > max_suffix) {
            max_suffix = suffix_sum;
        }
    }

    long long result = single_max;
    
    if (total_sum > 0) {
        long long candidate = max_suffix + (long long)(k - 2) * total_sum + max_prefix;
        if (candidate > result) {
            result = candidate;
        }
    } else {
        long long candidate = max_suffix + max_prefix;
        if (candidate > result) {
            result = candidate;
        }
    }

    return result;
}

int main(void) {
    int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
    
    long long result = max_sum_repeated_array(arr, n, k);
    printf("%lld\n", result);
    
    int arr2[] = {1, 2};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int k2 = 3;
    
    long long result2 = max_sum_repeated_array(arr2, n2, k2);
    printf("%lld\n", result2);
    
    int arr3[] = {-1, -2, -3};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int k3 = 2;
    
    long long result3 = max_sum_repeated_array(arr3, n3, k3);
    printf("%lld\n", result3);
    
    return 0;
}