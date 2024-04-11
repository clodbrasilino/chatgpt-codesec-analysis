#include <stdio.h>

int findLastRemoved(int arr[], int n, int removedElement) {
    int pos = -1;
    for(int i = 0; i < n; i++) {
        if(arr[i] == removedElement) {
            pos = i;
        }
    }
    return pos;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int removedElement = 5;
    int pos = findLastRemoved(arr, n, removedElement);
    if(pos != -1) {
        printf("The position of the last removed element is: %d\n", pos);
    } else {
        printf("Element not found in the array.\n");
    }
    return 0;
}