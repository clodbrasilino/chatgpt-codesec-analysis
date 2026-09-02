#include <stdio.h>

int findFixedPoint(int arr[], int size) {
    if (arr == NULL || size <= 0) {
        return -1;
    }
    
    for (int i = 0; i < size; i++) {
        if (arr[i] == i) {
            return i;
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