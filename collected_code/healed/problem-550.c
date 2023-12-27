#include <stdio.h>

int findMaxElement(const int arr[], int low, int high) {
    if (low == high) {
        return arr[low];
    }
    if (arr[low] == arr[high]) {
        return arr[low];
    }
    int mid = (low + high) / 2;
    if (arr[mid] > arr[mid + 1]) {
        return arr[mid];
    }
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