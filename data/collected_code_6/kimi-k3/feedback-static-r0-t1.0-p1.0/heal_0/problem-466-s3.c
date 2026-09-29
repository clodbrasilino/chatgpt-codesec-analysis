#include <stdio.h>
#include <stdlib.h>

int findPeakElement(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return -1;
    }
    
    if (n == 1) {
        return 0;
    }
    
    if (arr[0] >= arr[1]) {
        return 0;
    }
    
    if (arr[n - 1] >= arr[n - 2]) {
        return (int)(n - 1);
    }
    
    for (size_t i = 1; i < n - 1; i++) {
        if (arr[i] >= arr[i - 1] && arr[i] >= arr[i + 1]) {
            return (int)i;
        }
    }
    
    return -1;
}

int main(void) {
    int arr[] = {1, 3, 20, 4, 1, 0};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    
    int peakIndex = findPeakElement(arr, n);
    
    if (peakIndex >= 0) {
        printf("Peak element found at index %d with value %d\n", peakIndex, arr[peakIndex]);
    } else {
        printf("No peak element found\n");
    }
    
    return 0;
}