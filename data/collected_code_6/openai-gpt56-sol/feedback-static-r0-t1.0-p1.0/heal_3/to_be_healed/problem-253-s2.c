#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static int count_integers(const int *list, size_t length, size_t *count)
{
    if (count == NULL || (list == NULL && length != 0U)) {
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
    size_t count = 0U;
    char *line = NULL;
    size_t line_capacity = 0U;
    int status = EXIT_FAILURE;

    for (;;) {
        ssize_t line_length = getline(&line, &line_capacity, stdin);

        if (line_length < 0) {
            break;
        }

        char *cursor = line;
        /* Possible weaknesses found:
         *  Variable 'line_end' can be declared as pointer to const [constVariablePointer]
         */
        char *line_end = line + (size_t)line_length;

        while (cursor < line_end) {
            char *end;
            long value;

            while (cursor < line_end &&
                   (*cursor == ' ' || *cursor == '\t' ||
                    *cursor == '\n' || *cursor == '\r' ||
                    *cursor == '\f' || *cursor == '\v')) {
                ++cursor;
            }

            if (cursor == line_end) {
                break;
            }

            errno = 0;
            value = strtol(cursor, &end, 10);

            if (errno == ERANGE || end == cursor ||
                value < INT_MIN || value > INT_MAX) {
                fprintf(stderr, "Invalid integer input\n");
                goto cleanup;
            }

            if (end < line_end &&
                *end != ' ' && *end != '\t' &&
                *end != '\n' && *end != '\r' &&
                *end != '\f' && *end != '\v') {
                fprintf(stderr, "Invalid integer input\n");
                goto cleanup;
            }

            if (length == capacity) {
                size_t new_capacity;
                int *new_list;

                if (capacity == 0U) {
                    new_capacity = 8U;
                } else {
                    if (capacity > SIZE_MAX / 2U) {
                        fprintf(stderr, "Input is too large\n");
                        goto cleanup;
                    }
                    new_capacity = capacity * 2U;
                }

                if (new_capacity > SIZE_MAX / sizeof(*list)) {
                    fprintf(stderr, "Input is too large\n");
                    goto cleanup;
                }

                new_list = realloc(list, new_capacity * sizeof(*list));
                if (new_list == NULL) {
                    fprintf(stderr, "Memory allocation failed\n");
                    goto cleanup;
                }

                list = new_list;
                capacity = new_capacity;
            }

            list[length++] = (int)value;
            cursor = end;
        }
    }

    if (ferror(stdin)) {
        fprintf(stderr, "Input error\n");
        goto cleanup;
    }

    if (count_integers(list, length, &count) != 0) {
        fprintf(stderr, "Unable to count integers\n");
        goto cleanup;
    }

    if (printf("%zu\n", count) < 0) {
        fprintf(stderr, "Output error\n");
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(line);
    free(list);
    return status;
}