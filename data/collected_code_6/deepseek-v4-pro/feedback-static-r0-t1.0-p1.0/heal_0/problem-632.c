#include <stdio.h>
#include <stdlib.h>

void move_zeroes_to_end(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return;
    }

    int write_index = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] != 0) {
            if (write_index != i) {
                arr[write_index] = arr[i];
            }
            write_index++;
        }
    }

    for (int i = write_index; i < n; i++) {
        arr[i] = 0;
    }
}

int main(void) {
    int arr[] = {0, 1, 0, 3, 12, 0, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    move_zeroes_to_end(arr, n);

    printf("Array after moving zeroes to end:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}