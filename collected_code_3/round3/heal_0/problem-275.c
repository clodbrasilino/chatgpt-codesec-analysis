#include <stdio.h>

int findLastRemoved(int arr[], int n, int x) {
    int i;
    for (i = n - 1; i >= 0; i--) {
        if (arr[i] == x) {
            return i;
        }
    }
    return -1;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 5;
    int index = findLastRemoved(arr, n, x);
    if (index != -1) {
        printf("Element %d is present at index %d", x, index);
    } else {
        printf("Element %d is not present in array", x);
    }
    return 0;
}