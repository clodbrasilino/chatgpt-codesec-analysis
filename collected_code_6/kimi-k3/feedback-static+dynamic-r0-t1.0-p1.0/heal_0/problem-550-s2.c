#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_max(const int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return INT_MIN;
    }
    if (n == 1) {
        return arr[0];
    }
    
    int left = 0;
    int right = n - 1;
    
    if (arr[left] < arr[right]) {
        return arr[right];
    }
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (mid < n - 1 && arr[mid] > arr[mid + 1]) {
            return arr[mid];
        }
        if (mid > 0 && arr[mid - 1] > arr[mid]) {
            return arr[mid - 1];
        }
        
        if (arr[mid] >= arr[left]) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return arr[n - 1];
}

int main(void) {
    int arr1[] = {3, 4, 5, 1, 2};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", find_max(arr1, n1));
    
    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", find_max(arr2, n2));
    
    int arr3[] = {5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", find_max(arr3, n3));
    
    return EXIT_SUCCESS;
}