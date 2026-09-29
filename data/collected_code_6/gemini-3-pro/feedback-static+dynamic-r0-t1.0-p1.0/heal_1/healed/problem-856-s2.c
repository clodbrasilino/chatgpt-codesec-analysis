#include <stdio.h>
#include <stdlib.h>

int min_swaps(const int* arr, int size) {
    if (arr == NULL || size <= 0) {
        return -1;
    }

    int count_zero = 0;
    int swaps = 0;

    for (int i = size - 1; i >= 0; i--) {
        if (arr[i] == 0) {
            count_zero++;
        } else if (arr[i] == 1) {
            swaps += count_zero;
        } else {
            return -1;
        }
    }

    return swaps;
}

int main(void) {
    int arr[] = {1, 0, 1, 0, 0, 0, 1, 1};
    int size = sizeof(arr) / sizeof(arr[0]);

    int result = min_swaps(arr, size);
    if (result != -1) {
        printf("Minimum swaps required: %d\n", result);
    } else {
        printf("Invalid input array.\n");
    }

    return 0;
}