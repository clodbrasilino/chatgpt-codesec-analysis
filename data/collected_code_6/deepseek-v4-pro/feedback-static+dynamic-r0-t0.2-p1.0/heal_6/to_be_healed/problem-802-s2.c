#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 3
  *  test case 2 failed: expected 3, got 5
  */

int count_rotations(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }
    
    int low = 0, high = n - 1;
    
    while (low < high) {
        if (arr[low] < arr[high]) {
            return low;
        }
        
        int mid = low + (high - low) / 2;
        int next = (mid + 1) % n;
        int prev = (mid + n - 1) % n;
        
        if (arr[mid] <= arr[next] && arr[mid] <= arr[prev]) {
            return mid;
        }
        else if (arr[mid] <= arr[high]) {
            high = mid - 1;
        }
        else if (arr[mid] >= arr[low]) {
            low = mid + 1;
        }
    }
    
    return low;
}

int main(void) {
    int arr1[] = {15, 18, 2, 3, 6, 12};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("Rotations: %d\n", count_rotations(arr1, n1));
    
    int arr2[] = {7, 9, 11, 12, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("Rotations: %d\n", count_rotations(arr2, n2));
    
    int arr3[] = {7, 9, 11, 12, 15};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("Rotations: %d\n", count_rotations(arr3, n3));
    
    int arr4[] = {1, 2, 3, 4, 5};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("Rotations: %d\n", count_rotations(arr4, n4));
    
    int arr5[] = {5, 1, 2, 3, 4};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    printf("Rotations: %d\n", count_rotations(arr5, n5));
    
    return 0;
}