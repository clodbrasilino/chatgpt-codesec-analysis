#include <stdio.h>

int isSortedByCorners(int arr[], int size) {
    if (size < 2) {
        return 1;
    }
    
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