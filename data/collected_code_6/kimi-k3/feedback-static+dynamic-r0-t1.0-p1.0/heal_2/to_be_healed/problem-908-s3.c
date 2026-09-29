#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected -1, got <no output>
  *  test case 2 failed: expected 0, got <no output>
  *  test case 0 failed: expected 3, got <no output>
  */

int findFixedPoint(const int arr[], int n) {
    int low = 0;
    int high = n - 1;
    int result = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] == mid) {
            result = mid;
            high = mid - 1;
        } else if (arr[mid] < mid) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    return result;
}

int main(void) {
    int arr[] = {-10, -5, 0, 3, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int fixedPoint = findFixedPoint(arr, n);
    
    if (fixedPoint != -1) {
        printf("Fixed point is %d\n", fixedPoint);
    } else {
        printf("No fixed point found\n");
    }
    
    return EXIT_SUCCESS;
}