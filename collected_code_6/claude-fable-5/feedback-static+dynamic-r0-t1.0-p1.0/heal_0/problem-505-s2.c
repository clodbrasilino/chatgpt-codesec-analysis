#include <stdio.h>
#include <stddef.h>

void move_zeroes_to_end(int *arr, size_t n)
{
    size_t write_index = 0;
    size_t read_index;

    if (arr == NULL || n == 0) {
        return;
    }

    for (read_index = 0; read_index < n; read_index++) {
        if (arr[read_index] != 0) {
            arr[write_index] = arr[read_index];
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
            return 1;
        }
    }

    if (printf("\n") < 0) {
        return 1;
    }

    return 0;
}