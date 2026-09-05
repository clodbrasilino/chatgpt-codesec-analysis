#include <stdio.h>
#include <stdlib.h>

int find_element(const int *arr, int n, int rotations, int index) {
    if (arr == NULL || n <= 0 || index < 0 || index >= n) {
        return -1;
    }
    int effective_rotations = rotations % n;
    int original_index = (index - effective_rotations + n) % n;
    return arr[original_index];
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int rotations = 2;
    int index = 1;
    
    int result = find_element(arr, n, rotations, index);
    printf("Element at index %d after %d rotations is %d\n", index, rotations, result);
    
    result = find_element(NULL, 5, 2, 1);
    printf("Element for NULL array: %d\n", result);
    
    result = find_element(arr, n, 2, 5);
    printf("Element for out of bounds index: %d\n", result);

    return 0;
}