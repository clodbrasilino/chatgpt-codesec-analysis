#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <ctype.h>

static int count_integers(const int *list, size_t length, size_t *count)
{
    if (count == NULL || (list == NULL && length != 0U)) {
        return -1;
    }

    *count = length;
    return 0;
}

static int read_line(FILE *stream, char **buffer, size_t *capacity,
                     size_t *length, int *reached_eof)
{
    if (stream == NULL || buffer == NULL || capacity == NULL ||
        length == NULL || reached_eof == NULL) {
        return -1;
    }

    *length = 0U;
    *reached_eof = 0;

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                return -1;
            }

            *reached_eof = 1;
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (*length > SIZE_MAX - 2U) {
            return -1;
        }

        if (*capacity <= *length + 1U) {
            size_t required = *length + 2U;
            size_t new_capacity;
            char *temporary;

            if (*capacity == 0U) {
                new_capacity = 256U;
            } else if (*capacity > SIZE_MAX / 2U) {
                new_capacity = required;
            } else {
                new_capacity = *capacity * 2U;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            temporary = realloc(*buffer, new_capacity);
            if (temporary == NULL) {
                return -1;
            }

            *buffer = temporary;
            *capacity = new_capacity;
        }

        (*buffer)[*length] = (char)ch;
        ++*length;
    }

    if (*capacity <= *length) {
        size_t new_capacity;
        char *temporary;

        if (*length == SIZE_MAX) {
            return -1;
        }

        new_capacity = *length + 1U;
        temporary = realloc(*buffer, new_capacity);
        if (temporary == NULL) {
            return -1;
        }

        *buffer = temporary;
        *capacity = new_capacity;
    }

    (*buffer)[*length] = '\0';
    return 0;
}

static int append_integer(int **list, size_t *length, size_t *capacity,
                          int value)
{
    if (list == NULL || length == NULL || capacity == NULL ||
        *length > *capacity) {
        return -1;
    }

    if (*length == *capacity) {
        size_t new_capacity;
        int *temporary;

        if (*capacity == 0U) {
            new_capacity = 8U;
        } else {
            if (*capacity > SIZE_MAX / 2U) {
                return -1;
            }

            new_capacity = *capacity * 2U;
        }

        if (new_capacity > SIZE_MAX / sizeof **list) {
            return -1;
        }

        temporary = realloc(*list, new_capacity * sizeof **list);
        if (temporary == NULL) {
            return -1;
        }

        *list = temporary;
        *capacity = new_capacity;
    }

    (*list)[*length] = value;
    ++*length;
    return 0;
}

static int parse_line(const char *line, int **list, size_t *length,
                      size_t *capacity)
{
    const char *cursor;

    if (line == NULL || list == NULL || length == NULL || capacity == NULL) {
        return -1;
    }

    cursor = line;

    while (*cursor != '\0') {
        char *end;
        long value;

        while (isspace((unsigned char)*cursor) != 0) {
            ++cursor;
        }

        if (*cursor == '\0') {
            break;
        }

        errno = 0;
        value = strtol(cursor, &end, 10);

        if (end == cursor || errno == ERANGE ||
            value < INT_MIN || value > INT_MAX) {
            return -1;
        }

        if (*end != '\0' && isspace((unsigned char)*end) == 0) {
            return -1;
        }

        if (append_integer(list, length, capacity, (int)value) != 0) {
            return -1;
        }

        cursor = end;
    }

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
        size_t line_length;
        int reached_eof;

        if (read_line(stdin, &line, &line_capacity, &line_length,
                      &reached_eof) != 0) {
            goto cleanup;
        }

        if (line_length == 0U && reached_eof != 0) {
            break;
        }

        if (parse_line(line, &list, &length, &capacity) != 0) {
            goto cleanup;
        }

        if (reached_eof != 0) {
            break;
        }
    }

    if (count_integers(list, length, &count) != 0) {
        goto cleanup;
    }

    if (printf("%zu\n", count) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(line);
    free(list);
    return status;
}