#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool parse_int(const char *text, int *result)
{
    char *end;
    long value;

    if (text == NULL || result == NULL) {
        return false;
    }

    errno = 0;
    value = strtol(text, &end, 10);

    if (errno == ERANGE ||
        end == text ||
        *end != '\0' ||
        value < (long)INT_MIN ||
        value > (long)INT_MAX) {
        return false;
    }

    *result = (int)value;
    return true;
}

static bool remove_consecutive_duplicates(int *list,
                                          size_t length,
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

static bool print_list(const int *list, size_t length)
{
    size_t i;

    if (list == NULL && length != 0U) {
        return false;
    }

    for (i = 0U; i < length; ++i) {
        if (i != 0U && putchar(' ') == EOF) {
            return false;
        }

        if (printf("%d", list[i]) < 0) {
            return false;
        }
    }

    return putchar('\n') != EOF;
}

int main(int argc, char **argv)
{
    int *list;
    size_t length;
    size_t new_length;
    size_t i;
    int status;

    if (argc <= 1) {
        return print_list(NULL, 0U) ? EXIT_SUCCESS : EXIT_FAILURE;
    }

    length = (size_t)(argc - 1);

    if (length > SIZE_MAX / sizeof(*list)) {
        return EXIT_FAILURE;
    }

    list = malloc(length * sizeof(*list));
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    status = EXIT_FAILURE;

    for (i = 0U; i < length; ++i) {
        if (!parse_int(argv[i + 1U], &list[i])) {
            goto cleanup;
        }
    }

    if (!remove_consecutive_duplicates(list, length, &new_length)) {
        goto cleanup;
    }

    if (!print_list(list, new_length)) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(list);
    return status;
}