#include <stdio.h>

int findExtra(const int arr1[], const int arr2[], int n) {
    int left = 0, right = n - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr1[mid] == arr2[mid]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}

int main(void) {
    int arr1[] = {2, 4, 6, 8, 10, 12, 14};
    int arr2[] = {2, 4, 6, 8, 10, 12};
    int n = sizeof(arr1) / sizeof(arr1[0]);
    
    int index = findExtra(arr1, arr2, n);
    printf("Extra element index: %d\n", index);
    
    int arr3[] = {1, 3, 5, 7, 9, 11};
    int arr4[] = {1, 3, 5, 7, 9, 11, 13};
    int m = sizeof(arr4) / sizeof(arr4[0]);
    
    int index2 = findExtra(arr4, arr3, m);
    printf("Extra element index: %d\n", index2);
    
    return 0;
}