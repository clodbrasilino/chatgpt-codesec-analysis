#include <stdio.h>
#include <limits.h>

int findMin(int arr[], int low, int high) {
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (mid < high && arr[mid + 1] < arr[mid]) {
            return arr[mid + 1];
        }
        if (mid > low && arr[mid] < arr[mid - 1]) {
            return arr[mid];
        }
        if (arr[low] <= arr[mid]) {
            if (arr[low] < arr[high]) {
                return arr[low];
            } else {
                low = mid + 1;
            }
        } else {
            high = mid;
        }
    }
    return arr[low];
}

int main() {
    int arr[] = {4, 5, 6, 7, 0, 1, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("The minimum element is %d\n", findMin(arr, 0, n - 1));
    return 0;
}