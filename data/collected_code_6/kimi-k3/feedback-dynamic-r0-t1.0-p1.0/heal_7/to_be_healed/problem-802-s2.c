#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 3
  *  test case 2 failed: expected 3, got 5
  */

int countRotations(int arr[], int n) {
    if (n <= 1) {
        return 0;
    }
    
    int low = 0;
    int high = n - 1;
    
    if (arr[low] < arr[high]) {
        return 0;
    }
    
    while (low < high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] > arr[high]) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    
    return low;
}

int main(void) {
    int arr[] = {15, 18, 2, 3, 6, 12};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int rotations = countRotations(arr, n);
    printf("Number of rotations: %d\n", rotations);
    
    return 0;
}