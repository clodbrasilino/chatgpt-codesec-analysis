#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

static int minimum_swaps(const char *first, const char *second, size_t length)
{
    size_t mismatches_01 = 0;
    size_t mismatches_10 = 0;

    if (first == NULL || second == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if ((first[i] != '0' && first[i] != '1') ||
            (second[i] != '0' && second[i] != '1')) {
            return -1;
        }

        if (first[i] == '0' && second[i] == '1') {
            if (mismatches_01 == SIZE_MAX) {
                return -1;
            }
            ++mismatches_01;
        } else if (first[i] == '1' && second[i] == '0') {
            if (mismatches_10 == SIZE_MAX) {
                return -1;
            }
            ++mismatches_10;
        }
    }

    if (mismatches_01 != mismatches_10 ||
        mismatches_01 > (size_t)INT_MAX) {
        return -1;
    }

    return (int)mismatches_01;
}

static char *read_line(FILE *stream, size_t *line_length)
{
    size_t length = 0;
    size_t capacity = 64;
    char *buffer = NULL;

    if (stream == NULL || line_length == NULL) {
        return NULL;
    }

    *line_length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = fgetc(stream);

            if (next == EOF) {
                if (ferror(stream)) {
                    free(buffer);
                    return NULL;
                }
            } else if (next != '\n' && ungetc(next, stream) == EOF) {
                free(buffer);
                return NULL;
            }

            break;
        }

        if (length > SIZE_MAX - 2) {
            free(buffer);
            return NULL;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = required;
            } else {
                new_capacity = capacity * 2;
                if (new_capacity < required) {
                    new_capacity = required;
                }
            }

            if (new_capacity < required || new_capacity <= capacity) {
                free(buffer);
                return NULL;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line_length = length;
    return buffer;
}

int main(void)
{
    char *first;
    char *second;
    size_t first_length;
    size_t second_length;
    int result;

    first = read_line(stdin, &first_length);
    if (first == NULL) {
        return EXIT_FAILURE;
    }

    second = read_line(stdin, &second_length);
    if (second == NULL) {
        free(first);
        return EXIT_FAILURE;
    }

    if (first_length != second_length) {
        result = -1;
    } else {
        result = minimum_swaps(first, second, first_length);
    }

    if (printf("%d\n", result) < 0) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    free(first);
    free(second);

    return EXIT_SUCCESS;
}