#include <stdio.h>
#include <stdlib.h>

void move_zeroes_to_end(int *arr, size_t n)
{
    size_t write_index = 0;
    size_t i;

    if (arr == NULL || n == 0) {
        return;
    }

    for (i = 0; i < n; i++) {
        if (arr[i] != 0) {
            arr[write_index] = arr[i];
            write_index++;
        }
    }

    while (write_index < n) {
        arr[write_index] = 0;
        write_index++;
    }
}

int main(void)
{
    int arr[] = {0, 1, 0, 3, 12, 0, 5, 0};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t i;

    move_zeroes_to_end(arr, n);

    for (i = 0; i < n; i++) {
        if (printf("%d ", arr[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (printf("\n") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}