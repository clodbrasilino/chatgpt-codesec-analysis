#include <stdio.h>
#include <stdlib.h>

int getElementAtIndexAfterRotations(const int arr[], int n, int index, int rotations) {
    if (n <= 0 || index < 0 || index >= n) {
        return -1;
    }
    rotations = rotations % n;
    int newIndex = (index + rotations) % n;
    return arr[newIndex];
}

int main() {
    const int arr[] = {1, 2, 3, 4, 5, 6};
    int n = 6;
    int index = 3;
    int rotations = 2;

    int result = getElementAtIndexAfterRotations(arr, n, index, rotations);
    printf("Element at index %d after %d rotations: %d\n", index, rotations, result);

    return 0;
}