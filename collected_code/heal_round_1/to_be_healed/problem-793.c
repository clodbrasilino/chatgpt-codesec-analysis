#include<stdio.h>

int findLastPosition(int arr[], int n, int element) {
    int low = 0;
    int high = n-1;
    int result = -1;
  
    while (low <= high) {
        int mid = low + (high - low) / 2;
  
        // If element is found, update result and search to the right
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[mid]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[mid] == element) {
            result = mid;
            low = mid + 1;
        }
        // If element is greater, ignore the left half
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[mid]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        else if (arr[mid] < element) {
            low = mid + 1;
        }
        // If element is smaller, ignore the right half
        else {
            high = mid - 1;
        }
    }
  
    return result;
}

int main() {
    int arr[] = {2, 6, 8, 10, 10, 13, 16};
    int n = sizeof(arr) / sizeof(arr[0]);
    int element = 10;
    int lastPosition = findLastPosition(arr, n, element);
  
    if (lastPosition != -1) {
        printf("Last position of element %d is %d\n", element, lastPosition);
    }
    else {
        printf("Element %d not found in the array\n", element);
    }
  
    return 0;
}