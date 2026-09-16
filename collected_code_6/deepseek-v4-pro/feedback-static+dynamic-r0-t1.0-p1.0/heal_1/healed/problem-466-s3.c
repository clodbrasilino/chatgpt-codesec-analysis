#include <stdio.h>

int findPeakElement(const int arr[], int n) {
    if (n == 1) return 0;
    if (arr[0] >= arr[1]) return 0;
    if (arr[n - 1] >= arr[n - 2]) return n - 1;

    int low = 1, high = n - 2;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] >= arr[mid - 1] && arr[mid] >= arr[mid + 1]) {
            return mid;
        } else if (arr[mid] < arr[mid - 1]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

int main(void) {
    int arr[] = {1, 3, 20, 4, 1, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    int peakIndex = findPeakElement(arr, n);
    if (peakIndex != -1) {
        printf("Peak element %d found at index %d\n", arr[peakIndex], peakIndex);
    } else {
        printf("No peak element found\n");
    }
    return 0;
}