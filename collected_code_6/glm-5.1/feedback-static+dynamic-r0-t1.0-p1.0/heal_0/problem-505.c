#include <stdio.h>
#include <stdlib.h>

void move_zeroes(int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return;
    }
    size_t write_idx = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] != 0) {
            arr[write_idx++] = arr[i];
        }
    }
    while (write_idx < size) {
        arr[write_idx++] = 0;
    }
}

int main(void) {
    size_t size = 8;
    int *arr = malloc(size * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }
    arr[0] = 1;
    arr[1] = 0;
    arr[2] = 2;
    arr[3] = 0;
    arr[4] = 3;
    arr[5] = 0;
    arr[6] = 0;
    arr[7] = 4;

    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    move_zeroes(arr, size);

    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return EXIT_SUCCESS;
}