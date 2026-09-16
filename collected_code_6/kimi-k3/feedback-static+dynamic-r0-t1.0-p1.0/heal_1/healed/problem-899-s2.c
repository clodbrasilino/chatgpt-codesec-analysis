#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool canSortByCorners(const int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return false;
    }
    
    if (n == 1) {
        return true;
    }
    
    int left = 0;
    int right = n - 1;
    int expected = 1;
    
    while (left <= right) {
        if (arr[left] == expected) {
            left++;
            expected++;
        } else if (arr[right] == expected) {
            right--;
            expected++;
        } else {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    int arr1[] = {2, 3, 1, 4, 5};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    
    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    int arr3[] = {5, 4, 3, 2, 1};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    
    printf("Array 1: %s\n", canSortByCorners(arr1, n1) ? "Can be sorted" : "Cannot be sorted");
    printf("Array 2: %s\n", canSortByCorners(arr2, n2) ? "Can be sorted" : "Cannot be sorted");
    printf("Array 3: %s\n", canSortByCorners(arr3, n3) ? "Can be sorted" : "Cannot be sorted");
    
    return 0;
}