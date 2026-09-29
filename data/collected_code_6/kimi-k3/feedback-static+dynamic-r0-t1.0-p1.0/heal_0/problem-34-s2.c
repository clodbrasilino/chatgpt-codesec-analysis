#include <stdio.h>
#include <stdlib.h>

int findMissingNumber(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }
    
    size_t left = 0;
    size_t right = size - 1;
    
    if (arr[right] == (int)(right + arr[0])) {
        return -1;
    }
    
    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        
        if (mid > 0 && arr[mid] - arr[mid - 1] > 1) {
            return arr[mid] - 1;
        }
        if (mid < size - 1 && arr[mid + 1] - arr[mid] > 1) {
            return arr[mid] + 1;
        }
        
        if (arr[mid] == (int)(mid + arr[0])) {
            left = mid + 1;
        } else {
            if (mid == 0) {
                break;
            }
            right = mid - 1;
        }
    }
    
    return -1;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 6, 7, 8};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int missing = findMissingNumber(arr, size);
    
    if (missing != -1) {
        printf("Missing number: %d\n", missing);
    } else {
        printf("No missing number found\n");
    }
    
    return 0;
}