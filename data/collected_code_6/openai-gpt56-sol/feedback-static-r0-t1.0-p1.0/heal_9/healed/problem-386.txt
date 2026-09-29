#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int minimum_swaps(const char *str, size_t *result)
{
    size_t open_count = 0;
    size_t close_count = 0;
    size_t imbalance = 0;
    size_t swaps = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    for (const char *p = str; *p != '\0'; ++p) {
        if (*p == '[') {
            if (open_count == SIZE_MAX) {
                return -1;
            }

            ++open_count;

            if (imbalance != 0) {
                if (swaps > SIZE_MAX - imbalance) {
                    return -1;
                }

                swaps += imbalance;
                --imbalance;
            }
        } else if (*p == ']') {
            if (close_count == SIZE_MAX) {
                return -1;
            }

            ++close_count;

            if (close_count > open_count) {
                imbalance = close_count - open_count;
            }
        } else {
            return -1;
        }
    }

    if (open_count != close_count) {
        return -1;
    }

    *result = swaps;
    return 0;
}

static int grow_buffer(char **buffer, size_t *capacity)
{
    char *new_buffer;
    size_t new_capacity;

    if (buffer == NULL || *buffer == NULL || capacity == NULL ||
        *capacity == 0 || *capacity > SIZE_MAX / 2) {
        return -1;
    }

    new_capacity = *capacity * 2;
    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return -1;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 0;
}

static int append_character(char **buffer, size_t *length,
                            size_t *capacity, int character)
{
    if (buffer == NULL || *buffer == NULL || length == NULL ||
        capacity == NULL || *length == SIZE_MAX) {
        return -1;
    }

    if (*length >= *capacity - 1) {
        if (grow_buffer(buffer, capacity) != 0) {
            return -1;
        }
    }

    (*buffer)[*length] = (char)character;
    ++*length;
    return 0;
}

static int read_line(FILE *stream, char **buffer)
{
    size_t length = 0;
    size_t capacity = 64;
    char *data;

    if (stream == NULL || buffer == NULL) {
        return -1;
    }

    *buffer = NULL;
    data = malloc(capacity);
    if (data == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(data);
                return -1;
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
                    free(data);
                    return -1;
                }
            } else if (next != '\n') {
                if (ungetc(next, stream) == EOF) {
                    free(data);
                    return -1;
                }
            }

            break;
        }

        if (append_character(&data, &length, &capacity, ch) != 0) {
            free(data);
            return -1;
        }
    }

    data[length] = '\0';
    *buffer = data;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t swaps;

    if (read_line(stdin, &input) != 0) {
        return EXIT_FAILURE;
    }

    if (minimum_swaps(input, &swaps) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%zu\n", swaps) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}