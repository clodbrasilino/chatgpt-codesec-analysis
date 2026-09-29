#include <stdio.h>

int findFirstPosition(int arr[], int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    if (low < n && arr[low] == target)
        return low;
    return -1;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 5;
    int position = findFirstPosition(arr, n, target);
    if (position != -1)
        printf("Element found at position: %d\n", position + 1);
    else
        printf("Element not found in the array\n");
    return 0;
}