#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool remove_odd_numbers(int *list, size_t *length)
{
    size_t read_index;
    size_t write_index = 0;

    if (length == NULL || (*length > 0 && list == NULL)) {
        return false;
    }

    for (read_index = 0; read_index < *length; ++read_index) {
        if (list[read_index] % 2 == 0) {
            list[write_index] = list[read_index];
            ++write_index;
        }
    }

    *length = write_index;
    return true;
}

int main(void)
{
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t length = sizeof(list) / sizeof(list[0]);
    size_t index;

    if (!remove_odd_numbers(list, &length)) {
        return EXIT_FAILURE;
    }

    for (index = 0; index < length; ++index) {
        if (printf("%d%s", list[index], index + 1 < length ? " " : "\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    if (length == 0 && putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}