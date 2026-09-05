#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got 5
  *  test case 1 failed: expected 2, got 3
  */

int countRotations(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return -1;
    }
    if (n == 1) {
        return 0;
    }
    
    size_t left = 0;
    size_t right = n - 1;
    
    if (arr[left] <= arr[right]) {
        return 0;
    }
    
    while (left <= right) {
        if (left == right) {
            return (int)left;
        }
        
        size_t mid = left + (right - left) / 2;
        size_t next = (mid + 1) % n;
        size_t prev = (mid + n - 1) % n;
        
        if (arr[mid] <= arr[next] && arr[mid] <= arr[prev]) {
            return (int)mid;
        }
        
        if (arr[mid] <= arr[right]) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return 0;
}

int main(void) {
    int arr[] = {15, 18, 2, 3, 6, 12};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    
    int rotations = countRotations(arr, n);
    
    if (rotations >= 0) {
        printf("Number of rotations: %d\n", rotations);
    } else {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}