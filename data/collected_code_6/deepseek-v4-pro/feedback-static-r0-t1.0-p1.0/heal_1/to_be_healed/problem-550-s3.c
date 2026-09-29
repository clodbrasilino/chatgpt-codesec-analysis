#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int find_max_sorted_rotated(int arr[], int size) {
    if (size <= 0) {
        /* Possible weaknesses found:
         *  'INT_MIN' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'INT_MIN'
         */
        return INT_MIN;
    }
    if (size == 1) {
        return arr[0];
    }
    
    int left = 0;
    int right = size - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > arr[right]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    int pivot = left;
    if (pivot == 0) {
        return arr[size - 1];
    }
    return arr[pivot - 1];
}

int main(void) {
    int arr1[] = {4, 5, 6, 7, 0, 1, 2};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("Max in arr1: %d\n", find_max_sorted_rotated(arr1, size1));
    
    int arr2[] = {1, 2, 3, 4, 5};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("Max in arr2: %d\n", find_max_sorted_rotated(arr2, size2));
    
    int arr3[] = {8, 10, 2, 4, 6};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("Max in arr3: %d\n", find_max_sorted_rotated(arr3, size3));
    
    int arr4[] = {5};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("Max in arr4: %d\n", find_max_sorted_rotated(arr4, size4));
    
    return 0;
}