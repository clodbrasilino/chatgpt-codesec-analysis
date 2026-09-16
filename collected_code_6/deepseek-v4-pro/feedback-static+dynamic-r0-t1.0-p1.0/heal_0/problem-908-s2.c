#include <stdio.h>

int findFixedPoint(int arr[], int size) {
    int left = 0, right = size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == mid) {
            return mid;
        }
        else if (arr[mid] < mid) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    
    return -1;
}

int main(void) {
    int arr1[] = {-10, -5, 0, 3, 7};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    
    int arr2[] = {0, 2, 5, 8, 17};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    
    int arr3[] = {-10, -5, 3, 4, 7, 9};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    
    int result1 = findFixedPoint(arr1, size1);
    int result2 = findFixedPoint(arr2, size2);
    int result3 = findFixedPoint(arr3, size3);
    
    printf("Fixed point in arr1: %d\n", result1);
    printf("Fixed point in arr2: %d\n", result2);
    printf("Fixed point in arr3: %d\n", result3);
    
    return 0;
}