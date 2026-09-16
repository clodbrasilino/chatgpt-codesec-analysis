#include <stdio.h>
#include <stddef.h>

int find_first_occurrence(const int *arr, size_t size, int target, size_t *index) {
    if (arr == NULL || index == NULL) {
        return -1;
    }
    
    if (size == 0) {
        return 0;
    }
    
    size_t left = 0;
    size_t right = size - 1;
    size_t result = size;
    
    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            if (mid == 0) {
                break;
            }
            right = mid - 1;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            if (mid == 0) {
                break;
            }
            right = mid - 1;
        }
    }
    
    if (result != size) {
        *index = result;
        return 1;
    }
    
    return 0;
}

int main(void) {
    int arr[] = {1, 2, 2, 2, 3, 4, 4, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int target = 2;
    size_t index = 0;
    
    int status = find_first_occurrence(arr, size, target, &index);
    
    if (status == 1) {
        printf("First occurrence of %d is at index: %zu\n", target, index);
    } else if (status == 0) {
        printf("%d not found in array\n", target);
    } else {
        fprintf(stderr, "Error: Invalid arguments\n");
        return 1;
    }
    
    return 0;
}