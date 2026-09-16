#include <stdio.h>
#include <stdlib.h>

int findMaxSortedRotated(int arr[], int size) {
    if (size <= 0) {
        return -1;
    }
    
    int left = 0;
    int right = size - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] > arr[right]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return arr[left - 1 < 0 ? size - 1 : left - 1];
}

int main(void) {
    int arr1[] = {4, 5, 6, 7, 0, 1, 2};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", findMaxSortedRotated(arr1, size1));
    
    int arr2[] = {1, 2, 3, 4, 5};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", findMaxSortedRotated(arr2, size2));
    
    int arr3[] = {2, 1};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", findMaxSortedRotated(arr3, size3));
    
    int arr4[] = {1};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("%d\n", findMaxSortedRotated(arr4, size4));
    
    int arr5[] = {3, 4, 5, 1, 2};
    int size5 = sizeof(arr5) / sizeof(arr5[0]);
    printf("%d\n", findMaxSortedRotated(arr5, size5));
    
    return 0;
}