#include <stdio.h>

int findMaxElement(int arr[], int low, int high) {
    // If array has only one element
    if (low == high) {
        return arr[low];
    }
    
    // If array is not rotated or has all identical elements
    if (arr[low] == arr[high]) {
        return arr[low];
    }
    
    // Calculate mid index
    int mid = (low + high) / 2;
    
    // Check if mid element is the maximum element
    if (arr[mid] > arr[mid + 1]) {
        return arr[mid];
    }
    
    // If mid element is not maximum, recursively search in left and right subarrays
    if (arr[low] <= arr[mid]) {
        return findMaxElement(arr, mid + 1, high);
    } else {
        return findMaxElement(arr, low, mid);
    }
}

int main() {
    int arr[] = {4, 5, 6, 7, 1, 2, 3};
    int size = sizeof(arr) / sizeof(arr[0]);
    int maxElement = findMaxElement(arr, 0, size - 1);
    
    printf("Maximum element in the array is %d.", maxElement);
    
    return 0;
}