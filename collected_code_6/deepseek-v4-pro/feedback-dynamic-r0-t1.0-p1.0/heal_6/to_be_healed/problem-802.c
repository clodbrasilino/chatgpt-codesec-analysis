#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 3
  *  test case 2 failed: expected 3, got 5
  */

int count_rotations(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }
    
    int left = 0;
    int right = n - 1;
    
    while (left < right) {
        if (arr[left] < arr[right]) {
            return left;
        }
        
        int mid = left + (right - left) / 2;
        
        if (arr[mid] > arr[right]) {
            left = mid + 1;
        } else if (arr[mid] < arr[right]) {
            right = mid;
        } else {
            right--;
        }
    }
    
    return left;
}

int main(void) {
    int arr1[] = {15, 18, 2, 3, 6, 12};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int rotations1 = count_rotations(arr1, n1);
    printf("Rotations: %d\n", rotations1);
    
    int arr2[] = {7, 9, 11, 12, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int rotations2 = count_rotations(arr2, n2);
    printf("Rotations: %d\n", rotations2);
    
    int arr3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int rotations3 = count_rotations(arr3, n3);
    printf("Rotations: %d\n", rotations3);
    
    int arr4[] = {5};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    int rotations4 = count_rotations(arr4, n4);
    printf("Rotations: %d\n", rotations4);
    
    int *arr5 = NULL;
    int rotations5 = count_rotations(arr5, 0);
    printf("Rotations: %d\n", rotations5);
    
    return 0;
}