#include <stdio.h>
#include <stdlib.h>

static void move_zeroes_to_end(int *values, size_t length)
{
    size_t write_index = 0;

    if (values == NULL) {
        return;
    }

    for (size_t read_index = 0; read_index < length; ++read_index) {
        if (values[read_index] != 0) {
            values[write_index++] = values[read_index];
        }
    }

    while (write_index < length) {
        values[write_index++] = 0;
    }
}

int main(void)
{
    int values[] = {0, 1, 0, 3, 12, 0, 5};
    const size_t length = sizeof(values) / sizeof(values[0]);

    move_zeroes_to_end(values, length);

    for (size_t i = 0; i < length; ++i) {
        if (printf("%d%s", values[i], i + 1U < length ? " " : "\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}