#include <stdio.h>
#include <stdbool.h>

bool isMajority(const int arr[], int n, int x) {
    int first = -1;
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == x) {
            first = mid;
            right = mid - 1;
        } else if (arr[mid] < x) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    if (first == -1) {
        return false;
    }
    
    if (first + n / 2 < n && arr[first + n / 2] == x) {
        return true;
    }
    
    return false;
}

int main(void) {
    int arr1[] = {1, 2, 3, 3, 3, 3, 10};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int x1 = 3;
    
    if (isMajority(arr1, n1, x1)) {
        printf("%d appears more than %d times in arr1\n", x1, n1 / 2);
    } else {
        printf("%d does not appear more than %d times in arr1\n", x1, n1 / 2);
    }
    
    int arr2[] = {1, 1, 2, 2, 2, 2, 3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int x2 = 1;
    
    if (isMajority(arr2, n2, x2)) {
        printf("%d appears more than %d times in arr2\n", x2, n2 / 2);
    } else {
        printf("%d does not appear more than %d times in arr2\n", x2, n2 / 2);
    }
    
    int arr3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int x3 = 3;
    
    if (isMajority(arr3, n3, x3)) {
        printf("%d appears more than %d times in arr3\n", x3, n3 / 2);
    } else {
        printf("%d does not appear more than %d times in arr3\n", x3, n3 / 2);
    }
    
    return 0;
}