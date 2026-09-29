#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  */

int countRotations(const int arr[], int n) {
    int low = 0, high = n - 1;
    
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] > arr[high]) {
            low = mid + 1;
        } else if (arr[mid] < arr[high]) {
            high = mid;
        } else {
            high--;
        }
    }
    return low;
}

int main(void) {
    int arr[] = {15, 18, 2, 3, 6, 12};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int rotations = countRotations(arr, n);
    
    printf("%d\n", rotations);
    
    return 0;
}