#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool all_different(int arr[], size_t size) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                return false;
            }
        }
    }
    return true;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    
    int arr2[] = {1, 2, 3, 4, 1};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    
    int arr3[] = {5};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    
    int arr4[] = {};
    size_t size4 = sizeof(arr4) / sizeof(arr4[0]);
    
    printf("%s\n", all_different(arr1, size1) ? "true" : "false");
    printf("%s\n", all_different(arr2, size2) ? "true" : "false");
    printf("%s\n", all_different(arr3, size3) ? "true" : "false");
    printf("%s\n", all_different(arr4, size4) ? "true" : "false");
    
    return 0;
}