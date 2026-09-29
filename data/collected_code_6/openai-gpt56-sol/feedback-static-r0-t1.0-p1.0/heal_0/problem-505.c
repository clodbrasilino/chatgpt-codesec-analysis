#include <stdio.h>
#include <stdlib.h>

static void move_zeroes_to_end(int *array, size_t length)
{
    size_t write_index = 0;

    if (array == NULL) {
        return;
    }

    for (size_t read_index = 0; read_index < length; ++read_index) {
        if (array[read_index] != 0) {
            array[write_index++] = array[read_index];
        }
    }

    while (write_index < length) {
        array[write_index++] = 0;
    }
}

int main(void)
{
    int array[] = {0, 1, 0, 3, 12, 0, 5};
    const size_t length = sizeof(array) / sizeof(array[0]);

    move_zeroes_to_end(array, length);

    for (size_t index = 0; index < length; ++index) {
        if (printf("%s%d", index == 0 ? "" : " ", array[index]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}