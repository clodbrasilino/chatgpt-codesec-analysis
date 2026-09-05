#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int min_removals(int *arr, size_t n, int k) {
    if (arr == NULL || n == 0) {
        return 0;
    }
    
    qsort(arr, n, sizeof(int), compare);
    
    size_t max_keep = 1;
    size_t left = 0;
    
    for (size_t right = 0; right < n; right++) {
        while (left < right && arr[right] - arr[left] > k) {
            left++;
        }
        size_t window_size = right - left + 1;
        if (window_size > max_keep) {
            max_keep = window_size;
        }
    }
    
    return (int)(n - max_keep);
}

int main(void) {
    int arr[] = {1, 3, 4, 9, 10, 11, 12, 17, 20};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int k = 4;
    
    int result = min_removals(arr, n, k);
    printf("%d\n", result);
    
    return 0;
}