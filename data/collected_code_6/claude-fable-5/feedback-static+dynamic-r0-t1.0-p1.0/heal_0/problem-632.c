#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void move_zeroes_to_end(int *arr, size_t n)
{
    size_t write_index;
    size_t read_index;

    if (arr == NULL || n == 0U) {
        return;
    }

    write_index = 0U;
    for (read_index = 0U; read_index < n; read_index++) {
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

static int print_array(const int *arr, size_t n)
{
    size_t i;

    if (arr == NULL) {
        return -1;
    }

    for (i = 0U; i < n; i++) {
        if (printf("%d ", arr[i]) < 0) {
            return -1;
        }
    }

    if (printf("\n") < 0) {
        return -1;
    }

    return 0;
}

int main(void)
{
    int data[] = {0, 1, 0, 3, 12, 0, 5, 0};
    size_t n = sizeof(data) / sizeof(data[0]);

    if (print_array(data, n) != 0) {
        return EXIT_FAILURE;
    }

    move_zeroes_to_end(data, n);

    if (print_array(data, n) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}