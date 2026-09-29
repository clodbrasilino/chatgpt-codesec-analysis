#include <stdio.h>

int countRotations(const int arr[], int n) {
    int min = arr[0];
    int min_index = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
            min_index = i;
        }
    }
    return min_index;
}

int main() {
    const int arr[] = {7, 8, 9, 1, 2, 3, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int rotations = countRotations(arr, n);
    printf("Number of rotations required to generate a sorted array: %d", rotations);
    return 0;
}