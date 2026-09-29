#include <stdio.h>
#include <stdlib.h>

void move_zeroes(int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return;
    }

    size_t non_zero_index = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] != 0) {
            if (i != non_zero_index) {
                int temp = arr[non_zero_index];
                arr[non_zero_index] = arr[i];
                arr[i] = temp;
            }
            non_zero_index++;
        }
    }
}

int main(void) {
    size_t size = 8;
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    arr[0] = 1;
    arr[1] = 0;
    arr[2] = 2;
    arr[3] = 0;
    arr[4] = 3;
    arr[5] = 0;
    arr[6] = 4;
    arr[7] = 5;

    move_zeroes(arr, size);

    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    arr = NULL;

    return EXIT_SUCCESS;
}