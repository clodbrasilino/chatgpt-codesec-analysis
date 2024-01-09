#include <stdio.h>

int findPeakElement(int arr[], int n) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if ((mid == 0 || arr[mid] >= arr[mid - 1]) && (mid == n - 1 || arr[mid] >= arr[mid + 1])) {
            return arr[mid];
        } else if (mid > 0 && arr[mid - 1] > arr[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;  // no peak element found
}

int main() {
    int arr[] = {1, 2, 3, 4, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int peak = findPeakElement(arr, n);
    printf("Peak element is %d\n", peak);
    return 0;
}