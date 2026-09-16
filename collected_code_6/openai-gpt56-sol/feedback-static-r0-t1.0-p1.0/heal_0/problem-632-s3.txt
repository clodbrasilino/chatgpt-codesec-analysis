#include <stdio.h>
#include <stdlib.h>

static void move_zeroes(int *values, size_t count)
{
    size_t write_index = 0;

    for (size_t read_index = 0; read_index < count; ++read_index) {
        if (values[read_index] != 0) {
            values[write_index++] = values[read_index];
        }
    }

    while (write_index < count) {
        values[write_index++] = 0;
    }
}

int main(void)
{
    int values[] = {0, 1, 0, 3, 12, 0, 5};
    const size_t count = sizeof values / sizeof values[0];

    move_zeroes(values, count);

    for (size_t i = 0; i < count; ++i) {
        if (printf("%s%d", i == 0 ? "" : " ", values[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}