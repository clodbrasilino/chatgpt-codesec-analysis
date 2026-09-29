#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 3
  */

int countRotations(const int arr[], int n) {
    if (n <= 1) {
        return 0;
    }
    
    int low = 0;
    int high = n - 1;
    
    while (low <= high) {
        if (low == high) {
            return low;
        }
        
        int mid = low + (high - low) / 2;
        
        if (mid < high && arr[mid] > arr[mid + 1]) {
            return mid + 1;
        }
        if (mid > low && arr[mid] < arr[mid - 1]) {
            return mid;
        }
        
        if (arr[low] <= arr[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    return 0;
}

int main(void) {
    int arr[] = {15, 18, 2, 3, 6, 12};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int rotations = countRotations(arr, n);
    printf("Number of rotations: %d\n", rotations);
    
    return 0;
}