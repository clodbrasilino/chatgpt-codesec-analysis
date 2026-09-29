#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool check_even_indices_even_numbers(const int arr[], size_t size) {
    if (arr == NULL) {
        return false;
    }
    
    for (size_t i = 0; i < size; i += 2) {
        if (arr[i] % 2 != 0) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    int arr1[] = {2, 1, 4, 3, 6, 5};
    int arr2[] = {2, 1, 5, 3, 6, 5};
    int arr3[] = {};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t size3 = 0;
    
    printf("Array 1: %s\n", check_even_indices_even_numbers(arr1, size1) ? "true" : "false");
    printf("Array 2: %s\n", check_even_indices_even_numbers(arr2, size2) ? "true" : "false");
    printf("Array 3 (empty): %s\n", check_even_indices_even_numbers(arr3, size3) ? "true" : "false");
    printf("NULL array: %s\n", check_even_indices_even_numbers(NULL, 5) ? "true" : "false");
    
    return 0;
}