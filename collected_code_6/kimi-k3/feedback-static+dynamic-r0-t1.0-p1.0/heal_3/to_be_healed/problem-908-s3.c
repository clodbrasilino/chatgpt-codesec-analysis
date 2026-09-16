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
    int arr0[] = {-10, -5, 0, 3, 7};
    int n0 = sizeof(arr0) / sizeof(arr0[0]);
    printf("%d\n", findFixedPoint(arr0, n0));
    
    int arr1[] = {0, 2, 5, 8, 17};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", findFixedPoint(arr1, n1));
    
    int arr2[] = {-10, -5, 3, 4, 7, 9};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", findFixedPoint(arr2, n2));
    
    return EXIT_SUCCESS;
}