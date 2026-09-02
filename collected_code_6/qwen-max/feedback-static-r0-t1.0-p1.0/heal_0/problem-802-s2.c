#include <stdio.h>
#include <stdlib.h>

int count_rotations(int *arr, int n) {
    int i;
    for (i = 0; i < n - 1; ++i) {
        if (arr[i] > arr[i + 1]) {
            return i + 1;
        }
    }
    return 0;
}

int main() {
    int arr[] = {4, 5, 6, 7, 0, 1, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int rotations = count_rotations(arr, n);
    printf("Number of rotations required: %d\n", rotations);
    return 0;
}