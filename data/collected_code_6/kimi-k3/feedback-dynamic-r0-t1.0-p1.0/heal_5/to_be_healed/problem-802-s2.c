#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 3
  */

int countRotations(int arr[], int n) {
    if (n <= 1) {
        return 0;
    }
    
    int low = 0;
    int high = n - 1;
    
    while (low <= high) {
        if (arr[low] <= arr[high]) {
            return low;
        }
        
        int mid = low + (high - low) / 2;
        int next = (mid + 1) % n;
        int prev = (mid + n - 1) % n;
        
        if (arr[mid] <= arr[next] && arr[mid] <= arr[prev]) {
            return mid;
        }
        
        if (arr[mid] <= arr[high]) {
            high = mid - 1;
        } else {
            low = mid + 1;
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