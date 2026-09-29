#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int min_subsets_distinct(int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }
    
    int *sorted = malloc(n * sizeof(int));
    if (sorted == NULL) {
        return -1;
    }
    
    memcpy(sorted, arr, n * sizeof(int));
    qsort(sorted, n, sizeof(int), compare_ints);
    
    int max_freq = 1;
    int current_freq = 1;
    
    for (size_t i = 1; i < n; i++) {
        if (sorted[i] == sorted[i - 1]) {
            current_freq++;
            if (current_freq > max_freq) {
                max_freq = current_freq;
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