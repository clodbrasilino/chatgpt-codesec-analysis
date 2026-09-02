#include <stdio.h>
#include <stdlib.h>

int getElementAfterRotations(const int *arr, int n, int k, int index) {
    if (n == 0 || index < 0 || index >= n) {
        return -1;
    }
    k = k % n;
    int newIndex = (index + n - k) % n;
    return arr[newIndex];
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;
    int index = 3;

    int result = getElementAfterRotations(arr, n, k, index);
    printf("Element at index %d after %d rotations is %d\n", index, k, result);

    return 0;
}