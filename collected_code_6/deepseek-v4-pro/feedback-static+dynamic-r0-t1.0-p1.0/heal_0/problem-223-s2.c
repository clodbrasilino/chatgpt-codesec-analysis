#include <stdio.h>
#include <stdbool.h>

bool isMajority(int arr[], int n, int x) {
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
    
    int last = -1;
    left = 0;
    right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == x) {
            last = mid;
            left = mid + 1;
        } else if (arr[mid] < x) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    int count = last - first + 1;
    return count > n / 2;
}

int main(void) {
    int arr1[] = {1, 2, 3, 3, 3, 3, 10};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int x1 = 3;
    
    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int x2 = 3;
    
    printf("%s\n", isMajority(arr1, n1, x1) ? "true" : "false");
    printf("%s\n", isMajority(arr2, n2, x2) ? "true" : "false");
    
    return 0;
}