#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

static int count_integers(const int *list, size_t length, size_t *count)
{
    if ((list == NULL && length != 0U) || count == NULL) {
        return -1;
    }

    *count = length;
    return 0;
}

int main(void)
{
    int *list = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    char *buffer = NULL;
    size_t buffer_size = 256U;

    if (buffer_size > SIZE_MAX / sizeof *buffer) {
        fputs("Input buffer is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    buffer = malloc(buffer_size * sizeof *buffer);
    if (buffer == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    while (fgets(buffer, (int)buffer_size, stdin) != NULL) {
        char *cursor = buffer;

        while (*cursor != '\0') {
            char *end = NULL;
            long value;

            errno = 0;
            value = strtol(cursor, &end, 10);

            if (end == cursor) {
                ++cursor;
                continue;
            }

            if (errno == ERANGE || value < INT_MIN || value > INT_MAX) {
                free(buffer);
                free(list);
                fputs("Integer out of range.\n", stderr);
                return EXIT_FAILURE;
            }

            if (length == capacity) {
                size_t new_capacity;
                int *new_list;

                if (capacity == 0U) {
                    new_capacity = 16U;
                } else {
                    if (capacity > SIZE_MAX / 2U) {
                        free(buffer);
                        free(list);
                        fputs("List is too large.\n", stderr);
                        return EXIT_FAILURE;
                    }
                    new_capacity = capacity * 2U;
                }

                if (new_capacity > SIZE_MAX / sizeof *list) {
                    free(buffer);
                    free(list);
                    fputs("List is too large.\n", stderr);
                    return EXIT_FAILURE;
                }

                new_list = realloc(list, new_capacity * sizeof *list);
                if (new_list == NULL) {
                    free(buffer);
                    free(list);
                    fputs("Memory allocation failed.\n", stderr);
                    return EXIT_FAILURE;
                }

                list = new_list;
                capacity = new_capacity;
            }

            list[length++] = (int)value;
            cursor = end;
        }
    }

    free(buffer);

    if (ferror(stdin)) {
        free(list);
        fputs("Input error.\n", stderr);
        return EXIT_FAILURE;
    }

    {
        size_t count = 0U;

        if (count_integers(list, length, &count) != 0) {
            free(list);
            fputs("Unable to count integers.\n", stderr);
            return EXIT_FAILURE;
        }

        if (printf("%zu\n", count) < 0) {
            free(list);
            return EXIT_FAILURE;
        }
    }

    free(list);
    return EXIT_SUCCESS;
}