#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <errno.h>

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

long long min_operations_to_equal(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return -1;
    }
    
    if (n == 1) {
        return 0;
    }
    
    if (n > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    
    int *sorted = malloc(n * sizeof(int));
    if (sorted == NULL) {
        return -1;
    }
    
    memcpy(sorted, arr, n * sizeof(int));
    qsort(sorted, n, sizeof(int), compare_ints);
    
    int median = sorted[n / 2];
    long long operations = 0;
    
    for (size_t i = 0; i < n; i++) {
        long long diff = (long long)arr[i] - (long long)median;
        long long abs_diff = (diff < 0) ? -diff : diff;
        
        if (operations > LLONG_MAX - abs_diff) {
            free(sorted);
            return -1;
        }
        operations += abs_diff;
    }
    
    free(sorted);
    return operations;
}

int main(void) {
    size_t n;
    
    if (scanf("%zu", &n) != 1 || n == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Invalid input size\n");
        return EXIT_FAILURE;
    }
    
    int *arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }
    
    long long result = min_operations_to_equal(arr, n);
    if (result >= 0) {
        printf("%lld\n", result);
    } else {
        fprintf(stderr, "Computation error\n");
        free(arr);
        return EXIT_FAILURE;
    }
    
    free(arr);
    return EXIT_SUCCESS;
}