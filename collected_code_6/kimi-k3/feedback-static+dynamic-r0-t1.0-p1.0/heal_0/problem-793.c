#include <stdio.h>
#include <stdlib.h>

int find_last_position(const int *arr, size_t size, int target) {
    if (arr == NULL || size == 0) {
        return -1;
    }
    
    size_t left = 0;
    size_t right = size - 1;
    int result = -1;
    
    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = (int)mid;
            left = mid + 1;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            if (mid == 0) {
                break;
            }
            right = mid - 1;
        }
    }
    
    return result;
}

int main(void) {
    int arr[] = {1, 2, 2, 2, 3, 4, 4, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int target = 2;
    
    int position = find_last_position(arr, size, target);
    
    if (position != -1) {
        printf("Last position of %d is at index %d\n", target, position);
    } else {
        printf("Element %d not found in array\n", target);
    }
    
    return 0;
}