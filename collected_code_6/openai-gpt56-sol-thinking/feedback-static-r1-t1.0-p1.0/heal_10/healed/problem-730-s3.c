#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool remove_consecutive_duplicates(int *list, size_t length, size_t *new_length)
{
    size_t write_index;

    if (new_length == NULL || (list == NULL && length != 0U)) {
        return false;
    }

    if (length == 0U) {
        *new_length = 0U;
        return true;
    }

    write_index = 1U;

    for (size_t read_index = 1U; read_index < length; ++read_index) {
        if (list[read_index] != list[write_index - 1U]) {
            list[write_index] = list[read_index];
            ++write_index;
        }
    }

    *new_length = write_index;
    return true;
}

int main(int argc, char *argv[const])
{
    int *list;
    size_t length;
    size_t new_length;

    if (argc <= 1) {
        return putchar('\n') == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    length = (size_t)(argc - 1);

    if (length > SIZE_MAX / sizeof(*list)) {
        return EXIT_FAILURE;
    }

    list = malloc(length * sizeof(*list));
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        const char *const argument = argv[i + 1U];
        char *end;
        long value;

        errno = 0;
        value = strtol(argument, &end, 10);

        if (errno == ERANGE ||
            end == argument ||
            *end != '\0' ||
            value < INT_MIN ||
            value > INT_MAX) {
            free(list);
            return EXIT_FAILURE;
        }

        list[i] = (int)value;
    }

    if (!remove_consecutive_duplicates(list, length, &new_length)) {
        free(list);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < new_length; ++i) {
        if (i != 0U && putchar(' ') == EOF) {
            free(list);
            return EXIT_FAILURE;
        }

        if (printf("%d", list[i]) < 0) {
            free(list);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(list);
        return EXIT_FAILURE;
    }

    free(list);
    return EXIT_SUCCESS;
}