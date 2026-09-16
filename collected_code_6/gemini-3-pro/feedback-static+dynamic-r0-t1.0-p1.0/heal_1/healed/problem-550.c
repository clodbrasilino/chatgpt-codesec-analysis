#include <stdio.h>
#include <stdlib.h>

int findMax(int arr[], int low, int high) {
    if (low == high) {
        return arr[low];
    }
    
    if (high == low + 1) {
        if (arr[low] >= arr[high]) {
            return arr[low];
        } else {
            return arr[high];
        }
    }
    
    int mid = low + (high - low) / 2;
    
    if (arr[mid] > arr[mid + 1]) {
        return arr[mid];
    }
    if (arr[mid - 1] > arr[mid]) {
        return arr[mid - 1];
    }
    
    if (arr[low] > arr[mid]) {
        return findMax(arr, low, mid - 1);
    } else {
        return findMax(arr, mid + 1, high);
    }
}

int main(void) {
    int arr[] = {3, 4, 5, 1, 2};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    
    int max = findMax(arr, 0, (int)(n - 1));
    printf("The maximum element is %d\n", max);
    
    return EXIT_SUCCESS;
}