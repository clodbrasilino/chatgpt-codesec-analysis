#include <stdio.h>
#include <stdlib.h>

int findMin(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return -1;
    }
    
    size_t left = 0;
    size_t right = n - 1;
    
    if (arr[left] <= arr[right]) {
        return arr[left];
    }
    
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        
        if (mid > 0 && arr[mid] < arr[mid - 1]) {
            return arr[mid];
        }
        
        if (mid < n - 1 && arr[mid] > arr[mid + 1]) {
            return arr[mid + 1];
        }
        
        if (arr[mid] >= arr[left]) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return arr[left];
}

int main(void) {
    int arr1[] = {4, 5, 6, 7, 0, 1, 2};
    int arr2[] = {3, 4, 5, 1, 2};
    int arr3[] = {1, 2, 3, 4, 5};
    int arr4[] = {2, 1};
    int arr5[] = {1};
    
    printf("%d\n", findMin(arr1, sizeof(arr1) / sizeof(arr1[0])));
    printf("%d\n", findMin(arr2, sizeof(arr2) / sizeof(arr2[0])));
    printf("%d\n", findMin(arr3, sizeof(arr3) / sizeof(arr3[0])));
    printf("%d\n", findMin(arr4, sizeof(arr4) / sizeof(arr4[0])));
    printf("%d\n", findMin(arr5, sizeof(arr5) / sizeof(arr5[0])));
    printf("%d\n", findMin(NULL, 5));
    printf("%d\n", findMin(arr1, 0));
    
    return 0;
}