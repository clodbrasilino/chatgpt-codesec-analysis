#include <stdio.h>

int isSortedByCorners(int arr[], int size) {
    if (size < 2) {
        return 1;
    }
    
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[size-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (arr[0] > arr[size - 1]) {
        return 0;
    }
    
    return 1;
}

int main() {
    int arr[] = {5, 8, 10, 12, 4, 2};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    if (isSortedByCorners(arr, size)) {
        printf("The array can be sorted by picking only the corner elements.\n");
    } else {
        printf("The array cannot be sorted by picking only the corner elements.\n");
    }
    
    return 0;
}