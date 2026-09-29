#include <stdio.h>
#include <stdlib.h>

int findSmallestMissing(int* arr, int size) {
    if (arr == NULL || size <= 0) {
        return 1;
    }

    int i = 0;
    while (i < size) {
        if (arr[i] > 0 && arr[i] <= size && arr[arr[i] - 1] != arr[i]) {
            int temp = arr[arr[i] - 1];
            arr[arr[i] - 1] = arr[i];
            arr[i] = temp;
        } else {
            i++;
        }
    }

    for (i = 0; i < size; i++) {
        if (arr[i] != i + 1) {
            return i + 1;
        }
    }

    return size + 1;
}

int main(void) {
    int arr[] = {3, 4, -1, 1};
    int size = sizeof(arr) / sizeof(arr[0]);

    int missing = findSmallestMissing(arr, size);
    printf("Smallest missing positive integer is: %d\n", missing);

    return 0;
}