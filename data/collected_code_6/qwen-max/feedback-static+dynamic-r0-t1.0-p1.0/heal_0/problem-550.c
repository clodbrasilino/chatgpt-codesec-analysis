#include <stdio.h>

int findMaxElement(int arr[], int n) {
    int low = 0, high = n - 1;
    while (low <= high) {
        if (arr[low] <= arr[high])
            return arr[high];
        int mid = low + (high - low) / 2;
        int next = (mid + 1) % n;
        int prev = (mid + n - 1) % n;
        if (arr[mid] >= arr[next] && arr[mid] >= arr[prev])
            return arr[mid];
        else if (arr[mid] <= arr[high])
            high = mid - 1;
        else if (arr[mid] >= arr[low])
            low = mid + 1;
    }
    return -1; // Should not reach here
}

int main() {
    int arr[] = {4, 5, 6, 7, 0, 1, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int maxElement = findMaxElement(arr, n);
    printf("Maximum element: %d\n", maxElement);
    return 0;
}