#include <stdio.h>
#include <stdlib.h>

int findSingleElement(int arr[], int size) {
    int left = 0;
    int right = size - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (mid % 2 == 1) {
            mid--;
        }
        
        if (arr[mid] == arr[mid + 1]) {
            left = mid + 2;
        } else {
            right = mid;
        }
    }
    
    return arr[left];
}

int main(void) {
    int arr1[] = {1, 1, 2, 2, 3, 4, 4, 5, 5};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("Single element: %d\n", findSingleElement(arr1, size1));
    
    int arr2[] = {1, 1, 2, 3, 3, 4, 4, 5, 5, 6, 6};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("Single element: %d\n", findSingleElement(arr2, size2));
    
    int arr3[] = {10};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("Single element: %d\n", findSingleElement(arr3, size3));
    
    return 0;
}