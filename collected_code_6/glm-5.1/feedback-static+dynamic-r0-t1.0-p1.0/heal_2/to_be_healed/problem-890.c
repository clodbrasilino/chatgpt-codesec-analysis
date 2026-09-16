#include <stdio.h>
#include <stdlib.h>

int find_extra_element_index(const int *arr1, const int *arr2, int n) {
    int left = 0;
    int right = n - 1;
    int index = n;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (mid < n - 1 && arr1[mid] == arr2[mid]) {
            left = mid + 1;
        } else {
            index = mid;
            right = mid - 1;
        }
    }
    
    return index;
}

int main(void) {
    int arr1[] = {2, 4, 6, 8, 10, 12, 14};
    /* Possible weaknesses found:
     *  Variable 'arr2' can be declared as const array [constVariable]
     */
    int arr2[] = {2, 4, 6, 10, 12, 14};
    int n = sizeof(arr1) / sizeof(arr1[0]);
    
    int result = find_extra_element_index(arr1, arr2, n);
    printf("%d\n", result);
    
    return 0;
}