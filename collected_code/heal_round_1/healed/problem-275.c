#include <stdio.h>

int lastRemovedElementPosition(int arr[], int n) {
    if (n <= 0) {
        return -1;
    }

    int removedElement = arr[n - 1];
    int lastRemovedPos = -1;
  
    for (int i = 0; i < n; i++) {
        if (arr[i] == removedElement) {
            lastRemovedPos = i;
        }
    }
  
    return lastRemovedPos;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    int lastRemovedPos = lastRemovedElementPosition(arr, n);
  
    if (lastRemovedPos == -1) {
        printf("Array is empty or element not found.\n");
    } else {
        printf("Last removed element position: %d\n", lastRemovedPos);
    }

    return 0;
}