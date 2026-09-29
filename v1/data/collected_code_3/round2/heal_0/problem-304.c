#include <stdio.h>

int findElement(int arr[], int ranges[][2], int rotations, int index, int n) {
    for (int i = rotations - 1; i >= 0; i--) {
        int left = ranges[i][0];
        int right = ranges[i][1];

        if (left <= index && index <= right) {
            if (index == left)
                index = right;
            else
                index--;
        }
    }
    return arr[index];
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};

    int ranges[2][2] = {{0, 2}, {0, 3}};

    int rotations = 2;
    int index = 1;

    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Element at index %d after %d rotations is %d", index, rotations, findElement(arr, ranges, rotations, index, n));
    return 0;
}