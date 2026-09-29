#include <stdio.h>
#include <stdbool.h>

bool isMinHeap(const int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return false;
    }
    
    for (int i = 0; i <= (n - 2) / 2; i++) {
        if (2 * i + 1 < n && arr[i] > arr[2 * i + 1]) {
            return false;
        }
        
        if (2 * i + 2 < n && arr[i] > arr[2 * i + 2]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int arr1[] = {10, 15, 14, 25, 30};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    
    int arr2[] = {10, 15, 14, 8, 30};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    if (isMinHeap(arr1, n1)) {
        printf("arr1 is a min heap\n");
    } else {
        printf("arr1 is not a min heap\n");
    }
    
    if (isMinHeap(arr2, n2)) {
        printf("arr2 is a min heap\n");
    } else {
        printf("arr2 is not a min heap\n");
    }
    
    return 0;
}