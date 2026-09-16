#include <stdio.h>
#include <stdbool.h>

bool binarySearch(const int arr[], int size, int target, int *result) {
    if (arr == NULL || result == NULL || size <= 0) {
        return false;
    }
    
    int left = 0;
    int right = size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            *result = mid;
            return true;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return false;
}

int main(void) {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 23;
    int result;
    
    if (binarySearch(arr, size, target, &result)) {
        printf("Element found at index %d\n", result);
    } else {
        printf("Element not found\n");
    }
    
    return 0;
}