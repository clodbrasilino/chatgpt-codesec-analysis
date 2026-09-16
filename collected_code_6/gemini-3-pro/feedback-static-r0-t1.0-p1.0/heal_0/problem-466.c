#include <stdio.h>
#include <stdlib.h>

int find_peakElement(const int *arr, int low, int high, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }

    int mid = low + (high - low) / 2;

    if ((mid == 0 || arr[mid - 1] <= arr[mid]) && 
        (mid == n - 1 || arr[mid + 1] <= arr[mid])) {
        return mid;
    } else if (mid > 0 && arr[mid - 1] > arr[mid]) {
        return find_peakElement(arr, low, mid - 1, n);
    } else {
        return find_peakElement(arr, mid + 1, high, n);
    }
}

int find_peak(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }
    return find_peakElement(arr, 0, n - 1, n);
}

int main(void) {
    int arr[] = {1, 3, 20, 4, 1, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int peak_index = find_peak(arr, n);
    
    if (peak_index != -1) {
        printf("Index of a peak point is %d\n", peak_index);
        printf("Peak element is %d\n", arr[peak_index]);
    } else {
        printf("No peak element found or invalid array.\n");
    }

    return 0;
}