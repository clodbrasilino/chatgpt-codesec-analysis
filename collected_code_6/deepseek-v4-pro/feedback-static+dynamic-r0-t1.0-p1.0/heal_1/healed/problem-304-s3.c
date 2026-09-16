#include <stdio.h>
#include <stdlib.h>

int find_element_after_rotations(const int *arr, int n, int rotations, int index) {
    if (arr == NULL || n <= 0 || index < 0 || index >= n) {
        return -1;
    }
    
    rotations = rotations % n;
    if (rotations < 0) {
        rotations += n;
    }
    
    int new_index = (index - rotations + n) % n;
    return arr[new_index];
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int rotations = 2;
    int index = 3;
    int result = find_element_after_rotations(arr, n, rotations, index);
    
    if (result != -1) {
        printf("Element at index %d after %d rotations: %d\n", index, rotations, result);
    } else {
        printf("Invalid input parameters\n");
    }
    
    int arr2[] = {10, 20, 30, 40, 50};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int rotations2 = -3;
    int index2 = 2;
    int result2 = find_element_after_rotations(arr2, n2, rotations2, index2);
    
    if (result2 != -1) {
        printf("Element at index %d after %d rotations: %d\n", index2, rotations2, result2);
    } else {
        printf("Invalid input parameters\n");
    }
    
    return 0;
}