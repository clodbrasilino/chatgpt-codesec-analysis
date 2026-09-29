#include <stdio.h>
#include <stdlib.h>

int findElement(const int* arr, int n, int rotations, int index) {
    if (arr == NULL || n <= 0 || index < 0 || index >= n) {
        return -1;
    }
    
    rotations = rotations % n;
    
    int original_index = (index - rotations + n) % n;
    
    return arr[original_index];
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int rotations = 2;
    int index = 1;
    
    int result = findElement(arr, n, rotations, index);
    
    if (result != -1) {
        printf("%d\n", result);
    }
    
    return 0;
}