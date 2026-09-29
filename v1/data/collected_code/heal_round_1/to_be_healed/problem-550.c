#include <stdio.h>

int findMaxElement(int arr[], int low, int high) {
    // If array has only one element
    if (low == high) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[low]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        return arr[low];
    }
    
    // If array is not rotated or has all identical elements
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[high]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  Cannot determine that 'arr[low]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (arr[low] == arr[high]) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[low]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        return arr[low];
    }
    
    // Calculate mid index
    int mid = (low + high) / 2;
    
    // Check if mid element is the maximum element
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[mid+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  Cannot determine that 'arr[mid]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (arr[mid] > arr[mid + 1]) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[mid]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        return arr[mid];
    }
    
    // If mid element is not maximum, recursively search in left and right subarrays
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[mid]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  Cannot determine that 'arr[low]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (arr[low] <= arr[mid]) {
        return findMaxElement(arr, mid + 1, high);
    } else {
        return findMaxElement(arr, low, mid);
    }
}

int main() {
    int arr[] = {4, 5, 6, 7, 1, 2, 3};
    int size = sizeof(arr) / sizeof(arr[0]);
    int maxElement = findMaxElement(arr, 0, size - 1);
    
    printf("Maximum element in the array is %d.", maxElement);
    
    return 0;
}