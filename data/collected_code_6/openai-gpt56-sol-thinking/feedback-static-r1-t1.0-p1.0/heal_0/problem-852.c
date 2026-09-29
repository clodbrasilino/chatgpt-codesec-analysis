#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool remove_negative_numbers(int *list, size_t *length)
{
    size_t read_index;
    size_t write_index = 0;

    if (length == NULL || (list == NULL && *length != 0)) {
        return false;
    }

    for (read_index = 0; read_index < *length; ++read_index) {
        if (list[read_index] >= 0) {
            list[write_index] = list[read_index];
            ++write_index;
        }
    }

    *length = write_index;
    return true;
}

int main(void)
{
    int list[] = {4, -2, 0, 7, -9, 3, -1};
    size_t length = sizeof(list) / sizeof(list[0]);
    size_t index;

    if (!remove_negative_numbers(list, &length)) {
        return EXIT_FAILURE;
    }

    for (index = 0; index < length; ++index) {
        if (printf("%s%d", index == 0 ? "" : " ", list[index]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}