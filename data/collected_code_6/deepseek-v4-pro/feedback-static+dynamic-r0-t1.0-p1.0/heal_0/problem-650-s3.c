#include <stdio.h>
#include <stdbool.h>

bool arrays_equal(const int *arr1, size_t size1, const int *arr2, size_t size2) {
    if (size1 != size2) {
        return false;
    }
    
    for (size_t i = 0; i < size1; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 4, 5};
    int arr3[] = {1, 2, 3, 4, 6};
    int arr4[] = {1, 2, 3};
    
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    size_t size4 = sizeof(arr4) / sizeof(arr4[0]);
    
    printf("arr1 and arr2 are %s\n", arrays_equal(arr1, size1, arr2, size2) ? "equal" : "not equal");
    printf("arr1 and arr3 are %s\n", arrays_equal(arr1, size1, arr3, size3) ? "equal" : "not equal");
    printf("arr1 and arr4 are %s\n", arrays_equal(arr1, size1, arr4, size4) ? "equal" : "not equal");
    
    return 0;
}