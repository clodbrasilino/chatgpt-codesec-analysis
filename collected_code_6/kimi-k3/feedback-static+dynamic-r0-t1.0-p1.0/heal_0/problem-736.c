#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

size_t lower_bound(const int *arr, size_t n, int value) {
    size_t left = 0;
    size_t right = n;
    
    if (arr == NULL && n > 0) {
        return n;
    }
    
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (arr[mid] < value) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}

int main(void) {
    int arr[] = {1, 3, 5, 7, 9, 11};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int value = 6;
    size_t pos = lower_bound(arr, n, value);
    
    printf("Insertion point: %zu\n", pos);
    
    return EXIT_SUCCESS;
}