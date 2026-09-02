#include <stdio.h>

void move_zeroes_to_end(int arr[], int size) {
    if (arr == NULL || size <= 0) {
        return;
    }

    int non_zero_index = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] != 0) {
            arr[non_zero_index] = arr[i];
            non_zero_index++;
        }
    }

    while (non_zero_index < size) {
        arr[non_zero_index] = 0;
        non_zero_index++;
    }
}

int main(void) {
    int arr[] = {0, 1, 0, 3, 12, 0, 8};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    move_zeroes_to_end(arr, size);

    printf("Modified array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}