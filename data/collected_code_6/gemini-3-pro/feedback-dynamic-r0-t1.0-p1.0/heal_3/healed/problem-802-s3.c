#include <stdio.h>
#include <stdlib.h>

int countRotations(const int* arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }

    int min_index = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[min_index]) {
            min_index = i;
        }
    }

    return min_index;
}

int main(void) {
    int arr[] = {15, 18, 2, 3, 6, 12};
    int n = sizeof(arr) / sizeof(arr[0]);

    int rotations = countRotations(arr, n);

    if (rotations != -1) {
        printf("%d\n", rotations);
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}