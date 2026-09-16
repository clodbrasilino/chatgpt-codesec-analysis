#include <stdio.h>

int findSmallestMissing(const int arr[], int size) {
    int low = 0, high = size - 1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] == mid) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    return low;
}

int main(void) {
    int arr1[] = {0, 1, 2, 3, 4, 5};
    int arr2[] = {0, 1, 2, 4, 5, 6};
    int arr3[] = {1, 2, 3, 4, 5, 6};
    int arr4[] = {0, 1, 2, 3, 5, 6, 7};
    int arr5[] = {0};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    int size5 = sizeof(arr5) / sizeof(arr5[0]);
    
    printf("%d\n", findSmallestMissing(arr1, size1));
    printf("%d\n", findSmallestMissing(arr2, size2));
    printf("%d\n", findSmallestMissing(arr3, size3));
    printf("%d\n", findSmallestMissing(arr4, size4));
    printf("%d\n", findSmallestMissing(arr5, size5));
    
    return 0;
}