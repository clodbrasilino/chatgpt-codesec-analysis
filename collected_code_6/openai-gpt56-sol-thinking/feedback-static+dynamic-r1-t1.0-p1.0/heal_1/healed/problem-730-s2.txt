#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool remove_consecutive_duplicates(int *list, size_t length,
                                          size_t *new_length)
{
    size_t read_index;
    size_t write_index;

    if (new_length == NULL || (list == NULL && length != 0U)) {
        return false;
    }

    if (length == 0U) {
        *new_length = 0U;
        return true;
    }

    write_index = 1U;

    for (read_index = 1U; read_index < length; ++read_index) {
        if (list[read_index] != list[write_index - 1U]) {
            list[write_index] = list[read_index];
            ++write_index;
        }
    }

    *new_length = write_index;
    return true;
}

int main(void)
{
    int *list = NULL;
    size_t length;
    size_t new_length;
    size_t index;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*list)) {
        return EXIT_FAILURE;
    }

    if (length != 0U) {
        list = malloc(length * sizeof(*list));
        if (list == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (index = 0U; index < length; ++index) {
        if (scanf("%d", &list[index]) != 1) {
            free(list);
            return EXIT_FAILURE;
        }
    }

    if (!remove_consecutive_duplicates(list, length, &new_length)) {
        free(list);
        return EXIT_FAILURE;
    }

    for (index = 0U; index < new_length; ++index) {
        if (index != 0U && putchar(' ') == EOF) {
            free(list);
            return EXIT_FAILURE;
        }

        if (printf("%d", list[index]) < 0) {
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