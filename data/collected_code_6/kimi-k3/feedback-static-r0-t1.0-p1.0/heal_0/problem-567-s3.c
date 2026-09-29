#include <stdio.h>
#include <stdbool.h>

bool is_sorted(const int arr[], size_t size) {
    if (size <= 1) {
        return true;
    }
    
    for (size_t i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {5, 3, 4, 2, 1};
    int arr3[] = {1};
    
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    
    printf("Array 1 is %s\n", is_sorted(arr1, size1) ? "sorted" : "not sorted");
    printf("Array 2 is %s\n", is_sorted(arr2, size2) ? "sorted" : "not sorted");
    printf("Array 3 is %s\n", is_sorted(arr3, size3) ? "sorted" : "not sorted");
    
    return 0;
}