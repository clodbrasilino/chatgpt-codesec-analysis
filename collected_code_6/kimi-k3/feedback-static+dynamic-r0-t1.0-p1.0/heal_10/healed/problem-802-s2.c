#include <stdio.h>
#include <stdlib.h>

int countRotations(const int arr[], int n) {
    if (arr == NULL || n <= 1) {
        return 0;
    }
    
    int low = 0;
    int high = n - 1;
    
    if (arr[low] <= arr[high]) {
        return 0;
    }
    
    while (low < high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] > arr[high]) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    
    return low;
}

int main(void) {
    int arr1[] = {15, 18, 2, 3, 6, 12};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", countRotations(arr1, n1));
    
    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", countRotations(arr2, n2));
    
    int arr3[] = {5, 6, 7, 1, 2, 3, 4};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", countRotations(arr3, n3));
    
    return 0;
}