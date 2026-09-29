#include <stdio.h>
#include <stdlib.h>

int findPeakElement(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }

    int left = 0;
    int right = n - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > arr[mid + 1]) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;
}

int main(void) {
    int arr[] = {1, 2, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    int peakIndex = findPeakElement(arr, n);

    if (peakIndex != -1) {
        printf("Peak element is at index: %d\n", peakIndex);
        printf("Peak element value: %d\n", arr[peakIndex]);
    } else {
        printf("Invalid input array.\n");
    }

    return 0;
}