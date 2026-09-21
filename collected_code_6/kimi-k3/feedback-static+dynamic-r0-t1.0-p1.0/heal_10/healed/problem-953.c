#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int min_subsets_distinct(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }
    
    if (n > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    
    size_t alloc_size = n * sizeof(int);
    if (alloc_size == 0 || alloc_size / sizeof(int) != n) {
        return -1;
    }
    
    int *sorted = malloc(alloc_size);
    if (sorted == NULL) {
        return -1;
    }
    
    void *memcpy_result = memcpy(sorted, arr, alloc_size);
    if (memcpy_result != sorted) {
        free(sorted);
        return -1;
    }
    
    qsort(sorted, n, sizeof(int), compare_ints);
    
    int max_freq = 1;
    int current_freq = 1;
    
    for (size_t i = 1; i < n; i++) {
        if (sorted[i] == sorted[i - 1]) {
            if (current_freq < INT_MAX) {
                current_freq++;
                if (current_freq > max_freq) {
                    max_freq = current_freq;
                }
            }
        } else {
            current_freq = 1;
        }
    }
    
    free(sorted);
    return max_freq;
}

int main(void) {
    int arr[] = {1, 2, 3, 2, 4, 2, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    
    int result = min_subsets_distinct(arr, n);
    if (result >= 0) {
        printf("%d\n", result);
    }
    
    return 0;
}