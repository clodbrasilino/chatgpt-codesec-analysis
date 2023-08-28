#include <stdio.h>

int lastRemovedElementPosition(int arr[], int n) {
    int i, lastRemovedPos;
    int removedElement = arr[n - 1];

    for (i = 0; i < n; i++) {
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
    printf("Last removed element position: %d\n", lastRemovedPos);

    return 0;
}