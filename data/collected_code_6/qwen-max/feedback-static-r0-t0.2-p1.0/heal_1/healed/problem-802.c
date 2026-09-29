#include <stdio.h>
#include <stdlib.h>

int count_rotations(const int *arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        if (arr[i] > arr[i + 1]) {
            return i + 1;
        }
    }
    return 0;
}

int main() {
    int arr[] = {15, 18, 2, 3, 6, 12};
    int n = sizeof(arr) / sizeof(arr[0]);
    int rotations = count_rotations(arr, n);
    printf("Number of rotations: %d\n", rotations);
    return 0;
}