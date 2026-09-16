#include <stdio.h>
#include <stdlib.h>

size_t remove_odd_numbers(int *list, size_t length)
{
    size_t write_index = 0;

    if (list == NULL) {
        return 0;
    }

    for (size_t read_index = 0; read_index < length; ++read_index) {
        if (list[read_index] % 2 == 0) {
            list[write_index] = list[read_index];
            ++write_index;
        }
    }

    return write_index;
}

int main(void)
{
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t length = sizeof(list) / sizeof(list[0]);

    length = remove_odd_numbers(list, length);

    for (size_t index = 0; index < length; ++index) {
        if (printf("%s%d", index == 0 ? "" : " ", list[index]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}