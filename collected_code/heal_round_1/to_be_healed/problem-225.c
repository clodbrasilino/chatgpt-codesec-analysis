#include <stdio.h>

int findMinimum(int arr[], int low, int high)
{
    // If array is not rotated at all
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[high]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  Cannot determine that 'arr[low]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (arr[low] <= arr[high]) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[low]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        return arr[low];
    }
    
    // If only one element is left
    if (high == low + 1) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[high]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        return arr[high];
    }
    
    int mid = low + (high - low) / 2;
    
    // Check if mid element is minimum
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[mid+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  Cannot determine that 'arr[mid]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  Cannot determine that 'arr[mid-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (arr[mid] < arr[mid - 1] && arr[mid] < arr[mid + 1]) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[mid]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        return arr[mid];
    }
    
    // Decide whether to go left or right half
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[mid]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  Cannot determine that 'arr[high]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (arr[high] > arr[mid]) {
        return findMinimum(arr, low, mid -1);
    }
    else {
        return findMinimum(arr, mid + 1, high);
    }
}

int main()
{
    int arr[] = {4, 5, 6, 7, 8, 9, 1, 2, 3};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    int min = findMinimum(arr, 0, n - 1);
    
    printf("The minimum element in the array is: %d\n", min);
    
    return 0;
}