#include <stdio.h>
#include <stdlib.h>

int findMissingNumber(const int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return -1;
    }
    
    int low = 0;
    int high = size - 1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] == mid) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    return low;
}

int main(void) {
    int arr1[] = {0, 1, 2, 3, 5, 6, 7};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int missing1 = findMissingNumber(arr1, size1);
    printf("Missing number: %d\n", missing1);
    
    int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int missing2 = findMissingNumber(arr2, size2);
    printf("Missing number: %d\n", missing2);
    
    int arr3[] = {0, 1, 2, 3, 4, 5, 6, 7};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    int missing3 = findMissingNumber(arr3, size3);
    printf("Missing number: %d\n", missing3);
    
    /* Possible weaknesses found:
     *  Variable 'arr4' can be declared as pointer to const [constVariablePointer]
     */
    int *arr4 = NULL;
    int missing4 = findMissingNumber(arr4, 0);
    printf("Missing number: %d\n", missing4);
    
    return 0;
}