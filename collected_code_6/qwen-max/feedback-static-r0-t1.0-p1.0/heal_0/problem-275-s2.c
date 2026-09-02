#include <stdio.h>
#include <stdlib.h>

int findLastRemovedPosition(int *arr, int size, int removed) {
    for (int i = size - 1; i >= 0; --i) {
        if (arr[i] == removed) {
            return i;
        }
    }
    return -1;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int removed = 3;
    int pos = findLastRemovedPosition(arr, size, removed);
    if (pos != -1) {
        printf("Last removed element position: %d\n", pos);
    } else {
        printf("Element not found\n");
    }
    return 0;
}