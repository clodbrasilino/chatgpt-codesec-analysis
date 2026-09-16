#include <stdio.h>

int findFixedPoint(const int arr[], int size) {
    if (arr == NULL || size <= 0) {
        return -1;
    }
    
    int left = 0;
    int right = size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == mid) {
            return mid;
        } else if (arr[mid] < mid) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

int main(void) {
    int arr[] = {-10, -5, 0, 3, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    int result = findFixedPoint(arr, size);
    
    if (result != -1) {
        printf("Fixed point found at index %d\n", result);
    } else {
        printf("No fixed point found\n");
    }
    
    return 0;
}