#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int compare_ints(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

long long min_operations(int arr[], size_t n) {
    if (n == 0 || n == 1) return 0;
    
    qsort(arr, n, sizeof(int), compare_ints);
    
    long long total = 0;
    for (size_t i = 0; i < n; i++) {
        total += arr[i];
    }
    
    long long left_sum = 0;
    long long min_ops = LLONG_MAX;
    
    for (size_t i = 0; i < n; i++) {
        if (i > 0 && arr[i] == arr[i - 1]) {
            continue;
        }
        
        long long left_cost = (long long)arr[i] * (long long)i - left_sum;
        long long right_cost = (total - left_sum - arr[i]) - (long long)arr[i] * (long long)(n - i - 1);
        long long current_ops = left_cost + right_cost;
        
        if (current_ops < min_ops) {
            min_ops = current_ops;
        }
        
        left_sum += arr[i];
    }
    
    return min_ops;
}

int main(void) {
    size_t n;
    
    if (scanf("%zu", &n) != 1 || n == 0) {
        return EXIT_FAILURE;
    }
    
    int *arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return EXIT_FAILURE;
        }
    }
    
    long long result = min_operations(arr, n);
    printf("%lld\n", result);
    
    free(arr);
    return EXIT_SUCCESS;
}