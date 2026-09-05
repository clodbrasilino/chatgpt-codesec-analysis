#include <stdio.h>
#include <stdlib.h>

int find_single_element(const int *arr, size_t size, int *result) {
    if (arr == NULL || result == NULL || size == 0 || size % 2 == 0) {
        return -1;
    }
    
    size_t left = 0;
    size_t right = size - 1;
    
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        
        if (mid % 2 == 1) {
            mid--;
        }
        
        if (arr[mid] == arr[mid + 1]) {
            left = mid + 2;
        } else {
            right = mid;
        }
    }
    
    *result = arr[left];
    return 0;
}

int main(void) {
    int arr[] = {1, 1, 2, 2, 3, 4, 4, 5, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int result;
    
    if (find_single_element(arr, size, &result) == 0) {
        printf("%d\n", result);
    } else {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}