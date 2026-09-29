#include <stdio.h>
#include <stdlib.h>

int findLastRemovedPosition(const int arr[], int n, int removedElement) {
    int lastPosition = -1;
    int i;
    
    if (arr == NULL || n <= 0) {
        return -1;
    }
    
    for (i = n - 1; i >= 0; i--) {
        if (arr[i] == removedElement) {
            lastPosition = i;
            break;
        }
    }
    
    return lastPosition;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 3, 6, 7, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int removedElement = 3;
    int position;
    
    position = findLastRemovedPosition(arr, n, removedElement);
    
    if (position != -1) {
        printf("Last removed element position: %d\n", position);
    } else {
        printf("Element not found in array\n");
    }
    
    return 0;
}