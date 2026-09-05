#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool isMonotonic(const int* arr, size_t size) {
    if (arr == NULL || size == 0) {
        return false;
    }
    
    bool increasing = true;
    bool decreasing = true;
    
    for (size_t i = 1; i < size; i++) {
        if (arr[i] > arr[i - 1]) {
            decreasing = false;
        }
        if (arr[i] < arr[i - 1]) {
            increasing = false;
        }
    }
    
    return increasing || decreasing;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {5, 4, 3, 2, 1};
    int arr3[] = {1, 3, 2, 4, 5};
    int arr4[] = {1, 2, 2, 3, 4};
    
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    size_t size4 = sizeof(arr4) / sizeof(arr4[0]);
    
    printf("Array 1 is monotonic: %s\n", isMonotonic(arr1, size1) ? "true" : "false");
    printf("Array 2 is monotonic: %s\n", isMonotonic(arr2, size2) ? "true" : "false");
    printf("Array 3 is monotonic: %s\n", isMonotonic(arr3, size3) ? "true" : "false");
    printf("Array 4 is monotonic: %s\n", isMonotonic(arr4, size4) ? "true" : "false");
    
    return 0;
}