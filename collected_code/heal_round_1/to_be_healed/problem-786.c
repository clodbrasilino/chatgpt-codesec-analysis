#include <stdio.h>

int findInsertionPoint(int arr[], int n, int value) {
    int low = 0, high = n - 1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[mid]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[mid] == value)
            return mid;
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[mid]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        else if (arr[mid] < value)
            low = mid + 1;
        else
            high = mid - 1;
    }
    
    return low;
}

int main() {
    int arr[] = {1, 3, 5, 7, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int value = 6;
    
    int insertionPoint = findInsertionPoint(arr, n, value);
    
    printf("Insertion Point: %d", insertionPoint);
    
    return 0;
}