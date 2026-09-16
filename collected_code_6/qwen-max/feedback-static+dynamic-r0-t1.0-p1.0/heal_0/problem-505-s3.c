#include <stdio.h>
#include <stdlib.h>

void moveZeroesToEnd(int *array, int n) {
    if (n == 0) return;

    int nonZeroIndex = 0;

    for (int i = 0; i < n; ++i) {
        if (array[i] != 0) {
            if (i != nonZeroIndex) {
                array[nonZeroIndex] = array[i];
                array[i] = 0;
            }
            nonZeroIndex++;
        }
    }
}

int main() {
    int arr[] = {0, 1, 0, 3, 12};
    int n = sizeof(arr) / sizeof(arr[0]);

    moveZeroesToEnd(arr, n);

    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }

    return 0;
}